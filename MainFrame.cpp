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
    : MainFrameBaseClass(parent),
      close_requested(false),
      probing(false)
{
    const unsigned int num_nodes = config.nodes.size();
    const unsigned int num_cols = config.num_columns;

    // Create top-level grid sizer
    const unsigned int gap_width = 2;
    wxGridSizer *grid_sizer = new wxGridSizer(num_nodes, num_cols, gap_width, gap_width);

    // ??? Eventually figure out the cell_size from the format
    const wxSize font_size = GetFont().GetPixelSize();
    const wxSize cell_size(config.pane_width_chars*font_size.x, 
			   config.pane_height_lines*font_size.y);

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

    SetSizerAndFit(grid_sizer);
			  
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
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	// Delete each node object
	const std::string node_name = *nd;
	nodes[node_name]->setNodeDisplay(0);
	Node *node_to_delete = nodes[node_name];
	nodes[node_name] = 0;
	delete node_to_delete;
    }    

}


void MainFrame::OnClose(wxCloseEvent& event)
{
    if ( event.CanVeto() && probing )
    {
	close_requested = true;
	event.Veto();
	return;
    }

    Destroy(); 
}


void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
     if (probing)
	close_requested = true;
    else
	Close();
}

void MainFrame::OnCredits(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxString msg = 
	wxT("CREDITS") wxT("\n\n")
	wxT("   - INIH Library by Ben Hoyt") wxT("\n")
	wxT("     https://github.com/benhoyt/inih.git") wxT("\n\n")
	wxT("   - BOOST libraries\n")
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
    wxUnusedVar(event);
    probeAllNodes();
}

void MainFrame::OnRefresh(wxCommandEvent& event)
{
    wxUnusedVar(event);
    refresh();
}

void MainFrame::refresh()
{
    // Make each node display refresh itself (without probing)
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	nodes[node_name]->updateDisplay();
    }
}


void MainFrame::OnProbeAll(wxTimerEvent& event)
{
    wxUnusedVar(event);
    probeAllNodes();
}


void MainFrame::probeAllNodes()
{
    // Probe each node and redisplay
    for (NodeNameList::const_iterator nd = config.nodes.begin(); 
	 nd != config.nodes.end(); ++nd)
    {
	const std::string node_name = *nd;
	probing = true;
	nodes[node_name]->probe();
	nodes[node_name]->updateDisplay();
	probing = false;

	// If the user wants to quit, do it between pane updates
	if (close_requested) {
	    Destroy();
	    }
    }
}
