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

const unsigned char start_r = 230;
const unsigned char start_g = 230;
const unsigned char start_b = 230;

const unsigned char min_fails_color_r = 255;
const unsigned char min_fails_color_g = 204;
const unsigned char min_fails_color_b = 204;

const unsigned char max_fails_color_r = 255;
const unsigned char max_fails_color_g = 0;
const unsigned char max_fails_color_b = 0;


class ColorInterpolate;


class NodeDisplayPane : public wxTextCtrl, public NodeDisplay 
{
public:
    NodeDisplayPane(wxWindow *parent, const wxSize &cell_size);

    virtual ~NodeDisplayPane() {};

    virtual void updateDisplay(const Node &node);

    virtual void update();

    int numRows() const;
    int numCols() const;

protected:

    ColorInterpolate response_color;

    ColorInterpolate fail_color;

    wxColor start_color;
};


#endif /* end of  MESH_STAT_NODE_DISPLAY_PANE_H */
