/// NodeDisplayPane Class

#ifndef  MESH_STAT_NODE_DISPLAY_PANE_H
#define  MESH_STAT_NODE_DISPLAY_PANE_H

#include <wx/wx.h>

#include "NodeDisplay.h"


class NodeDisplayPane : public wxTextCtrl, public NodeDisplay 
{
public:
    NodeDisplayPane(wxWindow *parent, const wxSize &cell_size);

    void virtual updateDisplay(const Node &node);

};


#endif /* end of  MESH_STAT_NODE_DISPLAY_PANE_H */
