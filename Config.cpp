#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <boost/algorithm/string/split.hpp>                                      
#include <boost/algorithm/string.hpp> 

#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/filefn.h>
#include <wx/cmdline.h>
#include <wx/regex.h>
#include <wx/stdpaths.h>

#include "inih/ini.h"

#include "MainFrame.h"
extern MainFrame *main_frame_global;

#include "Config.h"

static std::string config_filename_local;

typedef std::map<std::string, unsigned int> DisplayModeNames;

static DisplayModeNames display_mode_names = {
    {"normal", NODE_DISPLAY_PANE},
    {"one-line", NODE_DISPLAY_PANE_ONE_LINE_STATUS}
};

static unsigned int max_display_mode_name_length = 0;

static std::map<unsigned int, std::string> display_mode_description = {
    { NODE_DISPLAY_PANE, "Normal 4-line display mode" },
    { NODE_DISPLAY_PANE_ONE_LINE_STATUS, "One-line status-only display mode"}
};


std::string findDisplayModeName(unsigned int index)
{
    for (DisplayModeNames::const_iterator iter = display_mode_names.begin(); 
	 iter != display_mode_names.end(); ++iter) 
    {
	if (index == (*iter).second)
	    return (*iter).first;
    }
    return std::string("");  // Should not happen
}



static const wxCmdLineEntryDesc g_cmdLineDesc[] =
{
    { wxCMD_LINE_SWITCH, "h", "help",    _("displays help on the command line parameters"), 
      wxCMD_LINE_VAL_NONE, 0 },

    { wxCMD_LINE_SWITCH, "v", "version", _("print version"), 
      wxCMD_LINE_VAL_NONE, 0 },

    { wxCMD_LINE_SWITCH, "g", "gencfg", _("write sample MeshStat.ini config file (and quit)"), 
      wxCMD_LINE_VAL_NONE, 0 },

    { wxCMD_LINE_SWITCH, "d", "dump", _("dump current configuration (and quit)"), 
      wxCMD_LINE_VAL_NONE, 0 },

    { wxCMD_LINE_OPTION, "n", "nodes", _("comma separated list of node(s) to monitor, with no spaces (overrides config file)"), 
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },

    { wxCMD_LINE_PARAM,  NULL, NULL, _("config file"), 
      wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
    
    { wxCMD_LINE_NONE, NULL, NULL, NULL, wxCMD_LINE_VAL_NONE, 0 }
};


static std::string cleanNodeURL(const std::string &raw_url, std::string &errmsg)
{
    // Return an empty string on failure

    // Remove comment, if any
    const std::string comment_delimiter = "#";
    std::string url(raw_url);
    if (url.find(comment_delimiter) != std::string::npos) 
    {
	url = url.substr(0, url.find(comment_delimiter));
	boost::algorithm::trim(url);
    }
    
    // Convert to lower case
    std::string url_lower_case(url);
    std::transform(url_lower_case.begin(), url_lower_case.end(), url_lower_case.begin(), ::tolower);
    boost::algorithm::trim(url_lower_case);

    // Complain about any protocol prefix
    const std::string protocol_delimiter = "://";
    if (url_lower_case.find(protocol_delimiter) != std::string::npos) 
    {
	std::string protocol = url_lower_case.substr(0, url_lower_case.find(protocol_delimiter));
	if (protocol == "https") {
	    std::stringstream msg;
	    msg << "ERROR!\n\nRemove the unsupported 'https://' protocol prefix \nfrom node name:\n\n"
		<< "  '" << raw_url << "'";
	    errmsg = msg.str();
	    return "";
	    }
	else {
	    std::stringstream msg;
	    msg << "ERROR!\n\nRemove the '" << protocol << "' protocol prefix \nfrom node name:\n\n"
		<< "  '" << raw_url << "'";
	    errmsg = msg.str();
	    return "";
	    }
    }

    // Accept numeric IP addresses
    const wxRegEx re_numeric("^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$");
    if (re_numeric.Matches(url)) {
	return url;
	}

    const wxRegEx re_multipart_hostname("^[-a-zA-Z0-9]+\\.[-a-zA-Z0-9]+(\\.[-a-zA-Z0-9]+)*$");
    if (re_multipart_hostname.Matches(url)) {
	return url;
	}

    const wxRegEx re_single_hostname("^[-a-zA-Z0-9]+$");
    if (re_single_hostname.Matches(url)) {
	url = url_lower_case + ".local.mesh";
	return url;
	}

    // Complain if we cannot parse the node name!
    std::stringstream msg;
    msg << "ERROR!\n\nUnrecognized node name syntax: \n\n"
	<< "  '" << url << "'";
    errmsg = msg.str();
    return "";
}


static int handler(void* configObj, const char *section_raw, 
		   const char *name_raw, const char *value_raw,
		   int lineno)
{
    ConfigInfo *config = reinterpret_cast<ConfigInfo *>(configObj);

    const std::string section(section_raw);
    const std::string name(name_raw);
    const std::string value(value_raw);

    if ((section != "Settings") and (section != "Nodes")) {
	std::stringstream msg;
	msg << "ERROR\n\nin config file: Unknown section name: \n\n" 
	    << "[" << name << "]"
	    << "\n\non line " << lineno << " of config file '" 
	    << config_filename_local << "'"
	    << "\n\nMust be either [Settings] or [Nodes] (case sensitve).\n";
	wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
	dialog.ShowModal();
        return 0;
	}
    
    if ((section == "Settings") && (name == "period")) {
	config->period = atof(value.c_str());
	}

    else if ((section == "Settings") && (name == "num_columns")) {
	config->num_columns = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "pane_width_chars")) {
	config->pane_width_chars = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "pane_height_lines")) {
	config->pane_height_lines = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "pane_border_width")) {
	config->pane_border_width = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "pane_interline_space")) {
	config->pane_interline_space = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "font_size")) {
	config->font_size = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "max_num_fails")) {
	config->max_num_fails = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "display_mode")) {
	std::string mode = value.c_str();
        boost::algorithm::trim(mode);
	std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
	if (display_mode_names.find(mode) == display_mode_names.end()) {
	    std::stringstream msg;
	    msg << "Display mode '" << mode << "' is not known!" << std::endl << std::endl;
	    msg << "Known modes: " << std::endl;
	    for (DisplayModeNames::const_iterator iter = display_mode_names.begin(); 
		 iter != display_mode_names.end(); ++iter) 
		msg << "   " << std::left << std::setw(max_display_mode_name_length) 
		    << (*iter).first << "  :  " << display_mode_description[(*iter).second] 
		    << "   " << std::endl;
	    wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
	    dialog.ShowModal();
	    return 0;
	    }
	else {
	    config->display_mode = display_mode_names[mode];
	    }
	}

    else if ((section == "Settings") && (name == "max_response_time")) {
	config->max_response_time = atoi(value.c_str());
	}

    else if ((section == "Settings") && (name == "node_access_timeout")) {
	config->node_access_timeout = atoi(value.c_str());
	}

    else if ((section == "Nodes")) {
	if (name == "node") {
	    std::string errmsg;
	    const std::string new_name = cleanNodeURL(value, errmsg);
	    if (new_name.empty()) {
		std::stringstream msg;
		msg << errmsg << "\n\non line " << lineno << " of config file '" 
		    << config_filename_local << "'" << std::endl;
		wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
		dialog.ShowModal();
		return 0;
		}
	    if (std::find(config->nodes.begin(), config->nodes.end(), new_name) == config->nodes.end()) {
		config->nodes.push_back(new_name);
		}
	    else {
		std::stringstream msg;
		msg << "ERROR\n\nDuplicate node name \n\n'" << new_name << "'"
		    << "\n\non line " << lineno << " of config file '" 
		    << config_filename_local << "'" << std::endl;
		wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
		dialog.ShowModal();
		return 0;
		}
	    }
	}

    else {
	std::stringstream msg;
	msg << "ERROR\n\nin config file: Unknown option name: \n\n" 
	    << "'" << name << "'\n\n in [" << section << "] section"
	    << "\n\n on line " << lineno << " of config file '" 
	    << config_filename_local << "'" << std::endl;
	wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
	dialog.ShowModal();
        return 0;
	}

    return 1;
}



ConfigInfo::ConfigInfo()
    : period(default_period),
      num_columns(default_num_columns),
      node_access_timeout(default_node_access_timeout),
      max_response_time(default_max_response_time),
      max_num_fails(default_max_num_fails),
      display_mode(default_display_mode),
      pane_width_chars(default_pane_width_chars),
      pane_height_lines(default_pane_height_lines),
      pane_border_width(default_pane_border_width),
      pane_interline_space(default_pane_interline_space),
      font_size(default_font_size)
{
}


bool ConfigInfo::parseCommandLine(int& argc, wxChar **argv)
{
    // Parse command line
    wxCmdLineParser cmdParser(g_cmdLineDesc, argc, argv);
    const int res = cmdParser.Parse(false);

    // Check if the user asked for command-line help 
    if (res == -1 || res > 0 || cmdParser.Found("h"))
    {
	cmdParser.AddUsageText("________________________________________________________________________\n\n");
	std::stringstream msg;
	msg << "You can specify a configuraton file in several ways:\n\n"
	    << " 1. Put a config file named 'MeshStat.ini' in either the directory\n"
	    << "     of this executable program or in the current directory.\n"
	    << " 2. Specifiy the name/path of the config file at the end of the command line.\n"
	    << " 3. Define an environment variable MESTSTAT_CONFIG_FILE with the full\n"
	    << "     path to the desired config file\n\n"
	    << "You can generate an example config file using the -g option.";
	cmdParser.AddUsageText(msg.str());
	
	// cmdParser.Usage();
	wxString help_msg = cmdParser.GetUsageString();
	wxMessageDialog dialog(main_frame_global, help_msg, _("Help"), wxICON_NONE);
	dialog.ShowModal();
	return false;
    }

    // Check if the user asked for the version
    if (cmdParser.Found("v"))
    {
	wxString date(wxString::FromAscii(__DATE__));
	std::stringstream msg;
	msg << "\nMeshStat\n\n(c) Jonathan M. Cameron KF6RTA  \n\n"
	    << "Version " << MESH_STAT_VERSION << ", " << date;
	wxMessageDialog dialog(main_frame_global, msg.str(), _("Version"), wxICON_INFORMATION);
	dialog.ShowModal();
	return false;
    }

    // Write the example config file
    if (cmdParser.Found("g"))
    {
	writeSampleConfigFile();
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
	    config_filename_local = configFilename;  // For the ini parser hander
	    }
	else {
	    std::stringstream msg;
	    msg << "ERROR\n\nUnable to find config file \n\n'" 
		<< fName.GetFullPath();
	    msg << "'\n\nspecified on the command line!  ";
	    wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
	    dialog.ShowModal();
	    return false;
	    }
    }
    else 
    {
	// If there is no config file on the command line, look for
	// MeshStat.ini in the current directory
	wxStandardPaths paths = wxStandardPathsBase::Get();
        wxFileName cfg_file_local("MeshStat.ini");
	wxFileName cfg_file_exe_path(paths.GetExecutablePath());
	wxFileName cfg_file_exe_dir(cfg_file_exe_path.GetPathWithSep());
	wxFileName cfg_file_exe(cfg_file_exe_dir.GetFullPath() + "MeshStat.ini");
	if (cfg_file_local.FileExists())
	{
	    // The MeshStat.ini file is in the directory MeshStat was run from
	    cfg_file_local.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
				     wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
	    config_filename = cfg_file_local.GetFullPath();
	}
	else if (cfg_file_exe.FileExists())
	{
	    // The MeshStat.ini file is in the directory containing the MeshStat executable
	    cfg_file_exe.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
				   wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
	    config_filename = cfg_file_exe.GetFullPath();
	}
	else 
	{
	    // If there is no MeshStat.ini file in the current directory or
	    // the directory of the executable, see if there is an environment
	    // variable pointing to it
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
		    std::stringstream msg;
		    msg << "ERROR\n\nUnable to find config file \n\n'" 
			<< fName.GetFullPath();
		    msg << "'\n\nfrom environment variable MESHSTAT_CONFIG_FILE!  ";
		    wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
		    dialog.ShowModal();
		    return false;
		}
	    }
	    else
	    {
		// Otherwise whine and stop
		std::stringstream msg;
		msg << "ERROR\n\nUnable to find config file! \n\n" 
		    << "Default: MeshStat.ini \n\n"
		    << "(in directory with MeshStat executable)   \n\n"
		    << "Use 'MeshStat -h' for help!";
		wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
		dialog.ShowModal();
		return false;
	    }
	}
    }

    // Figure out the maximum length of the display mode names
    for (DisplayModeNames::const_iterator iter = display_mode_names.begin(); 
	 iter != display_mode_names.end(); ++iter) 
    {
	const std::string mode = (*iter).first;
	if (mode.size() > max_display_mode_name_length)
	    max_display_mode_name_length = mode.size();
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
    
    // Make sure at least one node was given!
    if (nodes.size() == 0)
    {
	std::stringstream msg;
	msg << "ERROR in config file: \n\n" 
	    << "You must specify at least one node to monitor!";
	wxMessageDialog dialog(main_frame_global, msg.str(), _("ERROR"), wxICON_ERROR);
	dialog.ShowModal();
        return 0;
    }

    // Dump (if requested)
    if (cmdParser.Found("d")) 
    {
	dump();
	return false;
    }

    return true;
}

void ConfigInfo::writeSampleConfigFile() const
{
    std::string filename("MeshStat.ini");
    wxFileName fName(filename);
    fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
		    wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
    if (fName.FileExists())
    {
	std::stringstream msg;
	msg << "WARNING\n\n"
	    << "The file '" << filename << "' already exists!";
	wxMessageDialog dialog(main_frame_global, msg.str(), _("WARNING"), wxICON_WARNING|wxOK|wxCANCEL);
	dialog.SetOKLabel("Overwrite");
	const int result = dialog.ShowModal();
	if (result != wxID_OK) 
	    return;
    }

    wxFile file;
    if (!file.Open(fName.GetFullPath().c_str(), wxFile::write))
    {
	// wxWidgets puts up its own error dialog
	return;
    }

    std::stringstream ss;

    ss << "# Sample MeshStat.ini config file\n";
    ss << "\n";
    ss << "# NOTES: \n";
    ss << "#   - Do NOT indent any lines!\n";
    ss << "#   - Comment lines start with the # symbol\n";
    ss << "#   - Inline comments (on the end of a line) start with a semi-colon (;)";
    ss << "#   - If you uncomment any settings, remove any leading spaces!\n";
    ss << "#   - Commented out settings below show default values\n";
    ss << "#   - At minimum, you must uncomment and specify at \n";
    ss << "#     least one node in the [Nodes] section below!\n";
    ss << "\n";
    ss << "[Settings]\n";
    ss << "\n";
    ss << "# This is the general [Settings] section\n";
    ss << "\n";
    ss << "# Period between node status checks (seconds):\n";
    ss << "# (Should be larger than the number of nodes!)\n";
    ss << "# period = " << default_period << "  ; seconds\n";
    ss << "\n";
    ss << "# Number of columns in the node display: \n";
    ss << "# num_columns = " << default_num_columns << "\n";
    ss << "\n";
    ss << "# The desired display mode:\n";
    ss << "#   normal : Use normal 4-line display mode\n";
    ss << "#   one-line : Use one-line status only display mode\n";
    ss << "# display_mode = " << findDisplayModeName(default_display_mode) << "\n";
    ss << "\n";
    ss << "# Minimum node display pane width (characters)\n";
    ss << "# pane_width_chars = " << default_pane_width_chars << "\n";
    ss << "\n";
    ss << "# Minimum node display pane height (lines of text) - NOTE: Ignored in 1-line display mode\n";
    ss << "# pane_height_lines = " << default_pane_height_lines << "\n";
    ss << "\n";
    ss << "# Node display pane border width (pixels)\n";
    ss << "# pane_border_width = " << default_pane_border_width << "\n";
    ss << "\n";
    ss << "# Spacing on display pane between text lines (pixels)\n";
    ss << "# pane_interline_space = " << default_pane_interline_space << "\n";
    ss << "\n";
    ss << "# Font size to use in the node display: \n";
    ss << "# font_size = " << default_font_size << "\n";
    ss << "\n";
    ss << "# Max time allowed for node access timeout (seconds):\n";
    ss << "# (Node access longer than this is assumed to be a failed access)\n";
    ss << "# node_access_timeout = " << default_node_access_timeout << "\n";
    ss << "\n";
    ss << "# Max time allowed for normal responses (milliseconds):\n";
    ss << "# (Affects what shade of green the nodes are colored)\n";
    ss << "# (Faster response times are brighter green)\n";
    ss << "# max_response_time = " << default_max_response_time << "\n";
    ss << "\n";
    ss << "# Max number of access failures\n";
    ss << "# (Affects what shade of red the failing nodes are colored)\n";
    ss << "# (More failures than this colors the node display bright red)\n";
    ss << "# max_num_fails = " << default_max_num_fails << "\n";
    ss << "\n\n";
    ss << "[Nodes]\n";
    ss << "\n";
    ss << "# This is the [Nodes] section where you can specify which nodes to monitor\n";
    ss << "\n";
    ss << "# NOTES About the Mesh Nodes to Monitor: \n";
    ss << "#   - List the nodes to monitor below (do not indent any lines!)\n";
    ss << "#   - Repeat 'node = xx.yy.zz' on separate lines for each node to monitor\n";
    ss << "#   - Node names can be given as hostname or an IP address\n";
    ss << "#   - Giving node IP addresses will be faster since no DNS lookups are required\n";
    ss << "#   - Node names with no dots are assumed to be in the '.local.mesh' domain\n";
    ss << "#   - Do not use http:// or https:// prefixes\n";
    ss << "\n";
    ss << "# ADD YOUR OWN NODES BELOW\n";
    ss << "# (remove the leading comment symbol (#) and \n";
    ss << "#  any leading spaces from each active line)\n";
    ss << "\n";
    ss << "# node = mynode.local.mesh\n";
    ss << "# node = 10.123.45.67\n";
    ss << "# node = CALLSIGN-MR5\n";

    file.Write(ss.str());
    file.Close();
}


void ConfigInfo::dump() const
{
    std::stringstream msg;
    std::string filename = config_filename.GetFullPath().ToStdString();
    msg << std::endl << "Config file: \n  " << filename << std::endl;
    
    msg << std::endl << "Settings" << std::endl;
    msg << "  Period (seconds) = " << period;
    if (period == default_period) 
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_period << ")" << std::endl;

    msg << "  Num Columns = " << num_columns;
    if (num_columns == default_num_columns)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_num_columns << ")" << std::endl;

    msg << "  Display mode = " << findDisplayModeName(display_mode);
    if (display_mode == default_display_mode)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << findDisplayModeName(default_display_mode) << ")" << std::endl;

    msg << "  Node Access Timeout (milliseconds) = " << node_access_timeout;
    if (node_access_timeout == default_node_access_timeout)
	msg << "  (default)   " << std::endl;
    else
	msg << "  (default: " << default_node_access_timeout << ")   " << std::endl;

    msg << "  Max Response Time (milliseconds) = " << max_response_time;
    if (max_response_time == default_max_response_time)
	msg << "  (default)   " << std::endl;
    else
	msg << "  (default: " << default_max_response_time << ")   " << std::endl;

    msg << "  Max Num Fails = " << max_num_fails;
    if (max_num_fails == default_max_num_fails)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_max_num_fails << ")" << std::endl;

    msg << "  Node pane width (chars) = " << pane_width_chars;
    if (pane_width_chars == default_pane_width_chars)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_pane_width_chars << ")" << std::endl;

    msg << "  Pane border width = " << pane_border_width;
    if (pane_border_width == default_pane_border_width)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_pane_border_width << ")" << std::endl;

    msg << "  Pane spacing between lines (pixels) = " << pane_interline_space;
    if (pane_interline_space == default_pane_interline_space)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_pane_interline_space << ")" << std::endl;

    msg << "  Font size = " << font_size;
    if (font_size == default_font_size)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_font_size << ")" << std::endl;

    msg << "  Node pane height (lines of text) = " << pane_height_lines;
    if (pane_height_lines == default_pane_height_lines)
	msg << "  (default)" << std::endl;
    else
	msg << "  (default: " << default_pane_height_lines << ")" << std::endl;

    if (nodes.size() > 0) 
    {
	msg << std::endl << "Nodes:" << std::endl;
	for (NodeNameList::const_iterator nd=nodes.begin(); nd!=nodes.end(); ++nd)
	{
	    msg << "  " << *nd << std::endl;
	}
    }
    msg << std::endl;

    wxMessageDialog dialog(main_frame_global, msg.str(), _("Dump"), wxICON_INFORMATION);
    dialog.ShowModal();
}

