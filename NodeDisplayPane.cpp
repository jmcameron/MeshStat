#include "NodeDisplayPane.h"

NodeDisplayPane::NodeDisplayPane(wxWindow *parent, const wxSize &cell_size)
    : wxTextCtrl(parent, wxID_ANY, wxT(""), wxDefaultPosition, cell_size, wxTE_MULTILINE|wxTE_READONLY)
{

}
