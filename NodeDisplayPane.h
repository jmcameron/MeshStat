/// NodeDisplayPane Class

#ifndef  MESH_STAT_NODE_DISPLAY_PANE_H
#define  MESH_STAT_NODE_DISPLAY_PANE_H

#include <wx/wx.h>

#include "ColorInterpolate.h"

#include "NodeDisplay.h"

const unsigned char fast_color_r = 0;
const unsigned char fast_color_g = 255;
const unsigned char fast_color_b = 0;

const unsigned char slow_color_r = 204;
const unsigned char slow_color_g = 255;
const unsigned char slow_color_b = 204;


class ColorInterpolate;


class NodeDisplayPane : public wxTextCtrl, public NodeDisplay 
{
public:
    NodeDisplayPane(wxWindow *parent, const wxSize &cell_size);

    void virtual updateDisplay(const Node &node);

protected:
    ColorInterpolate response_color;

};


#endif /* end of  MESH_STAT_NODE_DISPLAY_PANE_H */
