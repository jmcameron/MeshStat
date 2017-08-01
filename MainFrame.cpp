#include "MainFrame.h"

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/aboutdlg.h>
#include <wx/url.h>
#include <wx/sstream.h>

#include <vector>
#include <string>

#include <unistd.h>

#include "NodeUtils.h"
#include "Config.h"


ConfigInfo config;


MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetVersion(MESH_STAT_VERSION);
    info.SetCopyright(_("Copyright (c) 2017\nJonathan M. Cameron, KF6RTA"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("MeshStat is a tool to periodically display the status of a set of mesh nodes simultaneously on a single screen."));
    ::wxAboutBox(info);
}


void MainFrame::OnTest1(wxCommandEvent& event)
{
    wxString htmldata;

    wxStopWatch timer;  // Start the timer

    wxURL url(wxT("http://mesh.w6jpl.ampr.org:8080/cgi-bin/sysinfo.json"));
 
    if(url.GetError()==wxURL_NOERR)
    {
 	wxInputStream *in = url.GetInputStream();
 	if(in && in->IsOk())
 	{
 	    wxStringOutputStream html_stream(&htmldata);
 	    in->Read(html_stream);
 	}
 	delete in;
    }
    else 
    {
 	htmldata = "";
    }
    timer.Pause();

    std::cerr << "FINISHED: " << timer.Time() << " ms" << std::endl;

//     std::string lines = std::string(htmldata.mb_str());

std::string lines("{\"channel\":\"174\",\"lat\":\"34.200464\",\"board_id\":\"0xe1b5\",\"api_version\":\"1.0\",\"model\":\"Ubiquiti Rocket M\",\"chanbw\":\"20\",\"tunnel_installed\":\"true\",\"ssid\":\"AREDN-20-v3\",\"node\":\"W6JPL-M5R-180R6\",\"lon\":\"-118.174341\",\"firmware_version\":\"3.16.1.1\",\"firmware_mfg\":\"AREDN\",\"grid_square\":\"\",\"active_tunnel_count\":\"0\",\"interfaces\":[{\"name\":\"eth0\",\"ip\":\"10.65.182.97\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.1\",\"ip\":\"44.16.15.50\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.2\",\"ip\":\"10.165.27.102\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"wlan0\",\"ip\":\"10.164.27.102\",\"mac\":\"24:A4:3C:A4:1B:66\"},{\"name\":\"wlan0-1\",\"ip\":\"none\",\"mac\":\"24-A4-3C-A4-1B-66-00-44-00-00-00-00-00-00-00-00\"}]}");

    NodeDataMap data;

    timer.Resume();
    getNodeDataJSON(data, lines);

    for (NodeDataMap::const_iterator dit = data.begin(); dit != data.end(); ++dit)
    {
	const std::string name(dit->first);
	const std::string val(dit->second);
	const std::string prt = name + std::string(": ") + val + std::string("\n");
	GetMainText()->AppendText(prt);
    }
    timer.Pause();

    wxString msg;
    msg.Printf("Loading: '%s'  (%ld ms)", config.config_filename.GetFullName().c_str(), timer.Time());
    GetMainText()->AppendText(msg);
}


