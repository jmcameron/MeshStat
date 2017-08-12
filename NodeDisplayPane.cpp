#include "Node.h"
#include "NodeDisplayPane.h"
#include "ColorInterpolate.h"


NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size, wxTE_MULTILINE|wxTE_READONLY)
{
    response_color.setColors(fast_color_r, fast_color_g, fast_color_b, 
			     slow_color_r, slow_color_g, slow_color_b);
}



void NodeDisplayPane::updateDisplay(const Node &node)
{
    // Clear the pane
    Clear();
    ClearBackground();

    AppendText(node.name);
}
