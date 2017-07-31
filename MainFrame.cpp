#include "MainFrame.h"

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/aboutdlg.h>
#include <wx/url.h>
#include <wx/sstream.h>

#include <vector>
#include <string>

#include <unistd.h>
#include <sys/time.h>

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


long int msec()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;    
}

double secs(const long int start_ms)
{
    return static_cast<double>(msec() - start_ms)/1000.0;
}

void MainFrame::OnTest1(wxCommandEvent& event)
{
    wxString htmldata;

    const long int start_ms = msec();

    std::cerr << "About to open URL " << secs(start_ms) << std::endl;
    wxURL url(wxT("http://mesh.w6jpl.ampr.org:8080/cgi-bin/sysinfo.json"));
    std::cerr << "Opened URL " << secs(start_ms) << std::endl;
 
    if(url.GetError()==wxURL_NOERR)
    {
	std::cerr << "Getting input  " << secs(start_ms) << std::endl;
	
 	wxInputStream *in = url.GetInputStream();

	std::cerr << "Getting input: OPENED " << secs(start_ms) << std::endl;
	std::cerr << "   DATA: " << in->CanRead() << std::endl;
  
 	if(in && in->IsOk())
 	{
	    std::cerr << "Getting input2 " << secs(start_ms) << std::endl;
 	    wxStringOutputStream html_stream(&htmldata);
	    std::cerr << "Getting input3 " << secs(start_ms) << std::endl;
 	    in->Read(html_stream);
	    std::cerr << "Getting input4 " << secs(start_ms) << std::endl;
 	}
 	delete in;
    }
    else 
    {
 	htmldata = "";
    }

    std::cerr << "FINISHED " << secs(start_ms) << std::endl;

//     std::string lines = std::string(htmldata.mb_str());

std::string lines("{\"channel\":\"174\",\"lat\":\"34.200464\",\"board_id\":\"0xe1b5\",\"api_version\":\"1.0\",\"model\":\"Ubiquiti Rocket M\",\"chanbw\":\"20\",\"tunnel_installed\":\"true\",\"ssid\":\"AREDN-20-v3\",\"node\":\"W6JPL-M5R-180R6\",\"lon\":\"-118.174341\",\"firmware_version\":\"3.16.1.1\",\"firmware_mfg\":\"AREDN\",\"grid_square\":\"\",\"active_tunnel_count\":\"0\",\"interfaces\":[{\"name\":\"eth0\",\"ip\":\"10.65.182.97\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.1\",\"ip\":\"44.16.15.50\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.2\",\"ip\":\"10.165.27.102\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"wlan0\",\"ip\":\"10.164.27.102\",\"mac\":\"24:A4:3C:A4:1B:66\"},{\"name\":\"wlan0-1\",\"ip\":\"none\",\"mac\":\"24-A4-3C-A4-1B-66-00-44-00-00-00-00-00-00-00-00\"}]}");

    NodeDataMap data;

    getNodeDataJSON(data, lines);

    for (NodeDataMap::const_iterator dit = data.begin(); dit != data.end(); ++dit)
    {
	const std::string name(dit->first);
	const std::string val(dit->second);
	const std::string prt = name + std::string(": ") + val + std::string("\n");
	GetMainText()->AppendText(prt);
    }

    wxString msg;
    msg.Printf("Loading: '%s'", config.config_filename.GetFullName().c_str());
    GetMainText()->AppendText(msg);
}


