#include <vector>
#include <string>
#include <sstream>

#include <math.h>
#include <unistd.h>

#include <wx/wx.h>
#include <wx/font.h>
#include <wx/sizer.h>
#include <wx/time.h>
#include <wx/aboutdlg.h>

#include "MainFrame.h"

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
    const unsigned int gap_width = config.pane_border_width;
    const unsigned int num_rows = ceil(static_cast<double>(num_nodes) / static_cast<double>(num_cols));;
    wxGridSizer *grid_sizer = new wxGridSizer(num_rows, num_cols, gap_width, gap_width);

    // Create the font for the panes
    wxFont pane_font(wxFontInfo(config.font_size).Family(wxFONTFAMILY_SWISS));

    // Create all the node objects
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

	// Create the pane
	NodeDisplayPane *pane = new NodeDisplayPane(this, wxSize(-1,-1));

	// Set up the font and compute the actual required size
	pane->SetFont(pane_font);
	wxClientDC dc(pane);
	dc.SetFont(pane_font);
	unsigned int num_lines = config.pane_height_lines;
	if (config.display_mode == NODE_DISPLAY_PANE_ONE_LINE_STATUS)
	    num_lines = 1;
	const unsigned int char_width = pane->GetCharWidth();   // This is the average width
	const unsigned int char_height = pane->GetCharHeight();
	const unsigned int interline_space = num_rows * config.pane_interline_space;
	const wxSize pane_size(config.pane_width_chars*char_width, 
			       num_lines*char_height + interline_space);

	/* DEBUG
	{
	    std::stringstream smsg;
	    smsg << "\nfont size w,h= " << char_width << "," << char_height  << std::endl;
	    wxMessageDialog sdialog(this, smsg.str(), _("Sizes"), wxICON_INFORMATION);
	    sdialog.ShowModal();
	} */

	pane->SetSize(pane_size);

	// Install the pane
	grid_sizer->Add(pane, 1, wxALL|wxFIXED_MINSIZE|wxEXPAND, config.pane_border_width);
	node_displays[node_name] = pane;
	nodes[node_name]->setNodeDisplay(pane);
    }

    SetSizerAndFit(grid_sizer);
			  
    // Freeze the size of the main window
    SetMinSize(GetSize());
    // SetMaxSize(GetSize());

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

    // Construct the description message
    std::stringstream msg;
    msg << "MeshStat is a tool to periodically display the status "
	<< "of a set of mesh nodes simultaneously on a single screen." << std::endl;

    // Compute the size of the pane
    NodeDisplayPane *pane0 = dynamic_cast<NodeDisplayPane *>(node_displays[config.nodes[0]]);
    if (pane0) {
	msg << "(pane size: rows=" << pane0->numRows() << ", columns=" << pane0->numCols() << ")";
	}

    info.SetDescription(msg.str());

    info.SetLicence(_("GPL v2 or later"));
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
    if (probing)
    {
	wxBell();
    }
    else
    {
	// If we are in the process of probing, NOP
	probeAllNodes();
    }

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

    // Tell the frame to update its display immediately
    Update();
}


void MainFrame::OnProbeAll(wxTimerEvent& event)
{
    wxUnusedVar(event);
    if (!probing)
	// If we are in the process of probing, NOP
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
