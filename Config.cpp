#include <string>
#include <vector>
#include <iterator>

#include <boost/algorithm/string/split.hpp>                                      
#include <boost/algorithm/string.hpp> 

#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/filefn.h>
#include <wx/cmdline.h>
#include <wx/regex.h>

#include "inih/ini.h"

#include "MainFrame.h"
#include "Config.h"


static const wxCmdLineEntryDesc g_cmdLineDesc[] =
{
    { wxCMD_LINE_SWITCH, "h", "help",    _("displays help on the command line parameters") },
    { wxCMD_LINE_SWITCH, "v", "version", _("print version") },

    { wxCMD_LINE_OPTION, "n", "nodes", _("node(s) to monitor, comma separated with no spaces (overrides config file)"), 
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },

    { wxCMD_LINE_SWITCH, "d", "dump", _("dump config (and quit)") },

    { wxCMD_LINE_PARAM,  NULL, NULL, _("config file"), 
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
    
    { wxCMD_LINE_NONE }
};


static std::string cleanNodeURL(const std::string &raw_url)
{
    // Return an empty string on failure

    // Remove comment, if any
    const std::string comment_delimiter = "#";
    std::string url(raw_url);
    if (url.find(comment_delimiter) != std::string::npos) 
    {
	url = url.substr(0, url.find(comment_delimiter));
	boost::algorithm::trim(url);
	std::cerr << "URL '" << url << "'" << std::endl;
    }
    
    std::string url_lower_case(url);
    std::transform(url_lower_case.begin(), url_lower_case.end(), url_lower_case.begin(), ::tolower);

    // Complain about any protocol prefix
    const std::string protocol_delimiter = "://";
    if (url_lower_case.find(protocol_delimiter) != std::string::npos) 
    {
	std::string protocol = url_lower_case.substr(0, url_lower_case.find(protocol_delimiter));
	if (protocol == "https") {
	    std::cerr << "ERROR: Remove unsupported 'https://' protocol prefix from node name '" << raw_url << "'" << std::endl;
	    return std::string();
	    }
	else {
	    std::cerr << "ERROR: Remove '" << protocol << "' protocol prefix from node name '" << raw_url << "'" << std::endl;
	    return std::string();
	    }
    }

    // Accept numeric IP addresses
    const wxRegEx re_numeric("^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$");
    if (re_numeric.Matches(url)) {
	return url;
	}

    const wxRegEx re_multipart_hostname("^[-a-zA-Z0-9]+\\.[-a-zA-Z0-9]+\\.[-a-zA-Z0-9]+(\\.[-a-zA-Z0-9]+)?$");
    if (re_multipart_hostname.Matches(url)) {
	return url;
	}

    const wxRegEx re_single_hostname("^[-a-zA-Z0-9]+$");
    if (re_single_hostname.Matches(url)) {
	url = url_lower_case + ".local.mesh";
	return url;
	}

    std::cerr << "ERROR: Unrecognized node name syntax: " << url << std::endl;
    return "";
}


static int handler(void* configObj, const char *section_raw, 
		   const char *name_raw, const char *value_raw)
{
    ConfigInfo *config = reinterpret_cast<ConfigInfo *>(configObj);

    const std::string section(section_raw);
    const std::string name(name_raw);
    const std::string value(value_raw);
    
    if ((section == "Settings") && (name == "num_columns")) {
	config->num_columns = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "max_num_fails")) {
	config->max_num_fails = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "max_response_time")) {
	config->max_response_time = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "period")) {
	config->period = atof(value.c_str());
	}

    else if ((section == "Nodes")) {
	if (name == "node") {
	    const std::string new_name = cleanNodeURL(value);
	    if (new_name.empty()) {
		return 0;
		}
	    if (std::find(config->nodes.begin(), config->nodes.end(), new_name) == config->nodes.end()) {
		config->nodes.push_back(new_name);
		}
	    else {
		std::cerr << "ERROR: Duplicate node name '" << new_name << "'" << std::endl;
		return 0;
		}
	    }
	}

    else {
	std::cerr << "ERROR in config file: Unknown section/name: " 
		  << section << "/" << name << std::endl;
        return 0;
	}

    return 1;
}



ConfigInfo::ConfigInfo()
{
    num_columns = 1;
    max_num_fails = default_max_num_fails;
    max_response_time = default_max_response_time;
    period = default_period;
}


bool ConfigInfo::parseCommandLine(int& argc, wxChar **argv)
{
    // Parse command line
    wxCmdLineParser cmdParser(g_cmdLineDesc, argc, argv);
    const int res = cmdParser.Parse(false);

    // Check if the user asked for command-line help 
    if (res == -1 || res > 0 || cmdParser.Found("h"))
    {
	std::cout << std::endl;
	cmdParser.Usage();
	std::cout << std::endl;
	return false;
    }

    // Check if the user asked for the version
    if (cmdParser.Found("v"))
    {
#ifndef __WXMSW__
	wxLog::SetActiveTarget(new wxLogStderr);
#endif
	wxString msg;
	wxString date(wxString::FromAscii(__DATE__));
	msg.Printf(_("\nMeshStat, (c) Jonathan M. Cameron KF6RTA, 2017 Version %s, %s\n"), 
		   MESH_STAT_VERSION, (const wxChar*) date);
	std::cout << msg << std::endl;
	return false;
    }

    // Check for a project filename
    if (cmdParser.GetParamCount() > 0)
    {
	// If a config file is specified, use it
	wxString configFilename = cmdParser.GetParam(0);

	// Under Windows when invoking via a document
	// in Explorer, we are passed the short form.
	// So normalize and make the long form.
	wxFileName fName(configFilename);
	fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
			wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
	if (fName.FileExists()) {
	    config_filename = fName;
	    }
	else {
	    wxString errmsg;
	    errmsg.Printf(_("\nERROR: Unable to find config file '%s' specified on the command line!\n"),
			  fName.GetFullPath().c_str());
	    std::cerr << errmsg << std::endl;
	    return false;
	    }
    }
    else 
    {
	// If there is no config file on the command line, look for
	// MeshStat.ini in the current directory
	wxFileName cfg_file("MeshStat.ini");
	if (cfg_file.FileExists())
	{
	    wxFileName fName(cfg_file);
	    fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
			    wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
	    config_filename = fName.GetFullPath();
	}
	else 
	{
	    // If there is no MeshStat.ini file in the current directory, see if
	    // there is an environment variable pointing to it
	    wxString env_filename;
	    if (wxGetEnv("MESHSTAT_CONFIG_FILE", &env_filename))
	    {
		wxFileName fName(env_filename);
		fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
				wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
		if (fName.FileExists()) 
		{
		    config_filename = fName.GetFullPath();
		}
		else
		{
		    wxString errmsg;
		    errmsg.Printf(_("\nERROR: Unable to find config file '%s' from environment variable MESHSTAT_CONFIG_FILE!\n"),
				  fName.GetFullPath().c_str());
		    std::cerr << errmsg << std::endl;
		    return false;
		}
	    }
	    else
	    {
		// Otherwise whine and stop
		wxString errmsg;
		errmsg.Printf(_("\nERROR: Unable to find config file! (default: MeshStat.ini)\n"));
		std::cerr << errmsg << std::endl;
		return false;
	    }
	}
    }

    // Load the parameter information from the config file
    std::string filename = config_filename.GetFullPath().ToStdString();
    int result = ini_parse(filename.c_str(), handler, this);
    if (result != 0) {
	if (result > 0) 
	    std::cerr << "ERROR: Cannot load config file '" 
		      << filename << "'; error on line " << result << "!" << std::endl;
	else
	    std::cerr << "ERROR: Cannot load config file '" 
		      << filename << "'! " << std::endl;
        return false;
    }

    // See if the user specified nodes on the command line
    wxString cmd_line_nodes;
    if (cmdParser.Found("n", &cmd_line_nodes))
    {
	typedef std::vector<std::string> StringVec;
	StringVec nodes;
	std::string nodes_raw = cmd_line_nodes.ToStdString();
	boost::algorithm::split(nodes,nodes_raw,boost::is_any_of(","),boost::token_compress_on);

	for (StringVec::const_iterator nd=nodes.begin(); nd!=nodes.end(); ++nd)
	{
	    // ??? copy to run list of nodes
	    std::cout << "  --> " << *nd << std::endl;
	}

	return false;
    }

    // Dump (if requested)
    if (cmdParser.Found("d")) 
    {
	dump();
	return false;
    }

    return true;
}


void ConfigInfo::dump() const
{
    std::string filename = config_filename.GetFullPath().ToStdString();
    std::cout << "Config file: " << filename << std::endl;
    std::cout << "  Num Columns = " << num_columns << std::endl;
    std::cout << "  Period = " << period << std::endl;
    std::cout << "  Max Num Fails = " << max_num_fails << std::endl;
    std::cout << "  Max Response Time = " << max_response_time << std::endl;

    if (nodes.size() > 0) 
    {
	std::cout << "  Nodes:" << std::endl;
	for (NodeNameList::const_iterator nd=nodes.begin(); nd!=nodes.end(); ++nd)
	{
	    std::cout << "   " << *nd << std::endl;
	}
    }
}

