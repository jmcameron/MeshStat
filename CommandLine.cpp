#include <wx/utils.h>
#include <wx/filefn.h>

#include "MainFrame.h"
#include "CommandLine.h"


static const wxCmdLineEntryDesc g_cmdLineDesc[] =
{
    { wxCMD_LINE_SWITCH, "h", "help",    _("displays help on the command line parameters") },
    { wxCMD_LINE_SWITCH, "v", "version", _("print version") },

    { wxCMD_LINE_PARAM,  NULL, NULL, _("config file"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },

    { wxCMD_LINE_NONE }
};


bool parseCommandLine(int& argc, wxChar **argv, MeshStatRunInfo &info)
{
    // Parse command line
    wxCmdLineParser cmdParser(g_cmdLineDesc, argc, argv);
    int res;
    {
	wxLogNull log;
	// Pass false to suppress auto Usage() message
	res = cmdParser.Parse(false);
    }

    // Check if the user asked for command-line help 
    if (res == -1 || res > 0 || cmdParser.Found(_("h")))
    {
	cmdParser.Usage();
	return false;
    }

    // Check if the user asked for the version
    if (cmdParser.Found(_("v")))
    {
#ifndef __WXMSW__
	wxLog::SetActiveTarget(new wxLogStderr);
#endif
	wxString msg;
	wxString date(wxString::FromAscii(__DATE__));
	msg.Printf(_("MeshStat, (c) Jonathan M. Cameron KF6RTA, 2017 Version %s, %s"), 
		   MESH_STAT_VERSION, (const wxChar*) date);
	wxLogMessage(msg);
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
	    info.filename = fName;
	    }
	else {
	    wxString errmsg;
	    errmsg.Printf(_("Unable to find config file '%s' from the command line!"),
			  fName.GetFullPath().c_str());
	    wxLogMessage(errmsg);
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
	    info.filename = fName.GetFullPath();
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
		    info.filename = fName.GetFullPath();
		}
		else
		{
		    wxString errmsg;
		    errmsg.Printf(_("Unable to find config file '%s' from environment variable MESHSTAT_CONFIG_FILE!"),
				  fName.GetFullPath().c_str());
		    wxLogMessage(errmsg);
		    return false;
		}
	    }
	    else
	    {
		// Otherwise whine and stop
		wxString errmsg;
		errmsg.Printf(_("Unable to find config file! (default: MeshStat.ini)"));
		wxLogMessage(errmsg);
		return false;
	    }
	}
    }

    return true;
}
