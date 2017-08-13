#include "MainFrame.h"

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/aboutdlg.h>

#include <vector>
#include <string>

#include <unistd.h>

#include "Config.h"

#include "NodeDisplayPane.h"


ConfigInfo config;


MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    const unsigned int num_nodes = config.nodes.size();

    // Create top-level grid sizer
    wxGridSizer *grid_sizer = new wxGridSizer(num_nodes+1, config.num_columns, 2, 2);
    SetSizer(grid_sizer);

    // ??? Eventually figure out the cell_size from the format
    const wxSize font_size = GetFont().GetPixelSize();
    const wxSize cell_size(60*font_size.x, 4*font_size.y);

    // Create all the panes for the nodes
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	nodes[node_name] = new Node(node_name);
    }
    
    // Create all the panes for the nodes
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	NodeDisplayPane *pane = new NodeDisplayPane(this, cell_size);
	grid_sizer->Add(pane, 1, wxALL|wxFIXED_MINSIZE, 3);
	node_displays[node_name] = pane;
	nodes[node_name]->setNodeDisplay(pane);
    }

    grid_sizer->Fit(this);

    // Freeze the size of the main window
    SetMinSize(GetSize());
    SetMaxSize(GetSize());

    // probe all the nodes
    probeAllNodes();

    // Start the periodic timer for the specified period
    m_timer->Start(static_cast<int>(config.period * 1000.0));
}

MainFrame::~MainFrame()
{
    // TODO ??? delete the node_displays
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnCredits(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxString msg = 
	wxT("CREDITS") wxT("\n\n")
	wxT("   - INIH Library by Ben Hoyt") wxT("\n")
	wxT("     https://github.com/benhoyt/inih.git") wxT("\n\n")
	wxT("   - Boost libraries\n")
	wxT("     http://www.boost.org/users/license.html") wxT("\n\n");

    wxMessageDialog dialog(this, msg, _("Credits"), wxICON_NONE);

    // dialog.SetBackgroundColour(wxColour(* wxWHITE)); 
    dialog.ShowModal();
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
    probeAllNodes();

//     wxString htmldata;
// 
//     wxStopWatch timer;  // Start the timer
// 
//     // const std::string test_host("mesh.w6jpl.ampr.org");
//     const std::string test_host("184.177.20.233");
//     // const std::string test_host("bogus.hostname.bad");
//     const std::string test_url = std::string("http://") + test_host + ":8080/cgi-bin/sysinfo.json";
// 
//     std::cerr << "OPEN URL: " << test_url << " at " << timer.Time() << " ms" << std::endl;
//     wxURL url(test_url.c_str());
//     // wxURL url(wxT("http://mesh.w6jpl.ampr.org:8080/cgi-bin/sysinfo.json"));
//     std::cerr << "URL OK: " << url.IsOk() << std::endl;
// 
//     if(url.GetError()==wxURL_NOERR)
//     {
// 	std::cerr << "GET INPUT STREAM: " << timer.Time() << " ms" << std::endl;
//  	wxInputStream *in = url.GetInputStream();
//  	if(in && in->IsOk())
//  	{
// 	    std::cerr << "CAN READ: " << in->CanRead() << std::endl;
// 
//  	    wxStringOutputStream html_stream(&htmldata);
// 	    std::cerr << "READ INPUT STREAM: " << timer.Time() << " ms" << std::endl;
//  	    in->Read(html_stream);
// 	    std::cerr << "READ INPUT STREAM DONE: " << timer.Time() << " ms" << std::endl;
//  	}
//  	delete in;
//     }
//     else 
//     {
// 	std::cerr << "ERROR OPENING URL: " << test_url << " at "<< timer.Time() << " ms" << std::endl;
//  	htmldata = "";
//     }
//     timer.Pause();
// 
//     std::cerr << "FINISHED: " << timer.Time() << " ms" << std::endl;
//     std::cerr << "DATA READ: " << htmldata.size() << std::endl;
// 
//     if (htmldata.size() > 0)
//     {
// 	std::string lines = std::string(htmldata.mb_str());
// 
// 	// std::string lines("{\"channel\":\"174\",\"lat\":\"34.200464\",\"board_id\":\"0xe1b5\",\"api_version\":\"1.0\",\"model\":\"Ubiquiti Rocket M\",\"chanbw\":\"20\",\"tunnel_installed\":\"true\",\"ssid\":\"AREDN-20-v3\",\"node\":\"W6JPL-M5R-180R6\",\"lon\":\"-118.174341\",\"firmware_version\":\"3.16.1.1\",\"firmware_mfg\":\"AREDN\",\"grid_square\":\"\",\"active_tunnel_count\":\"0\",\"interfaces\":[{\"name\":\"eth0\",\"ip\":\"10.65.182.97\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.1\",\"ip\":\"44.16.15.50\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"eth0.2\",\"ip\":\"10.165.27.102\",\"mac\":\"24:A4:3C:A5:1B:66\"},{\"name\":\"wlan0\",\"ip\":\"10.164.27.102\",\"mac\":\"24:A4:3C:A4:1B:66\"},{\"name\":\"wlan0-1\",\"ip\":\"none\",\"mac\":\"24-A4-3C-A4-1B-66-00-44-00-00-00-00-00-00-00-00\"}]}");
// 
// 	NodeDataMap data;
// 
// 	timer.Resume();
// 
// 	std::cerr << "START PARSING: " << timer.Time() << " ms" << std::endl;
// 	getNodeDataJSON(data, lines);
// 	std::cerr << "END PARSING: " << timer.Time() << " ms" << std::endl;
// 
// 	for (NodeDataMap::const_iterator dit = data.begin(); dit != data.end(); ++dit)
// 	{
// 	    const std::string name(dit->first);
// 	    const std::string val(dit->second);
// 	    const std::string prt = name + std::string(": ") + val + std::string("\n");
// 	    GetMainText()->AppendText(prt);
// 	}
// 	timer.Pause();
// 
//     }
//     else
//     {
// 	std::string msg = std::string("ERROR: Unable to read data from ") + test_url + "\n";
// 	GetMainText()->AppendText(msg);
//     }
// 
//     wxString msg;
//     msg.Printf("Loading: '%s'  (%ld ms)", config.config_filename.GetFullName().c_str(), timer.Time());
//     GetMainText()->AppendText(msg);
}

void MainFrame::OnRefresh(wxCommandEvent& event)
{
    wxUnusedVar(event);
    refresh();
}

void MainFrame::refresh()
{
    // Make each node display refresh itself
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	nodes[node_name]->updateDisplay();
    }
}


void MainFrame::OnProbeAll(wxTimerEvent& event)
{
    probeAllNodes();
}

void MainFrame::probeAllNodes()
{
    // Make each node display refresh itself
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	nodes[node_name]->probe();
	nodes[node_name]->updateDisplay();
    }
}
