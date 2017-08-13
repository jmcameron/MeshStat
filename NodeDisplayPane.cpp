#include <algorithm>  // max()

#include "Defaults.h"
#include "Node.h"
#include "NodeDisplayPane.h"
#include "ColorInterpolate.h"


NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size, wxTE_MULTILINE|wxTE_READONLY)
{
    start_color.Set(start_r, start_g, start_b);

    response_color.setColors(fast_color_r, fast_color_g, fast_color_b, 
			     slow_color_r, slow_color_g, slow_color_b);

    fail_color.setColors(min_fails_color_r, min_fails_color_g, min_fails_color_b, 
			 max_fails_color_r, max_fails_color_g, max_fails_color_b);
}



void NodeDisplayPane::updateDisplay(const Node &node)
{
    wxColour *bg_color;

    // Figure out the color for the background
    if (node.num_fails < 0) {
	bg_color = new wxColour(start_color);
	}
    else if (node.num_fails > 0) {
	double factor = 0.0;
	if (static_cast<unsigned int>(node.num_fails) >= max_num_fails)
	    factor = 1.0;
	else
	    factor = static_cast<double>(node.num_fails)/static_cast<double>(max_num_fails);
	bg_color = fail_color.color(factor);
	}
    else {
	double factor = 0.0;
	if (node.last_response_time >= max_response_time)
	    factor = 1.0;
	else
	    factor = static_cast<double>(node.last_response_time)/static_cast<double>(max_num_fails);
	bg_color = response_color.color(factor);
	}

    // Clear the pane
    Clear();
    SetBackgroundColour(*bg_color);
    ClearBackground();

    wxTextAttr ta;
    ta.SetFontWeight(wxFONTWEIGHT_BOLD);
    SetDefaultStyle(ta); 
    AppendText(node.name);

    ta.SetFontWeight(wxFONTWEIGHT_NORMAL);
    SetDefaultStyle(ta); 
    AppendText(wxT("\nThis is a test"));

    delete bg_color;
}
