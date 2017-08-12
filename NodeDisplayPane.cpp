#include "Node.h"
#include "NodeDisplayPane.h"

NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size, wxTE_MULTILINE|wxTE_READONLY)
{
}



void NodeDisplayPane::updateDisplay(const Node &node)
{
    // Clear the pane
    Clear();
    ClearBackground();

    AppendText(node.name);
}
