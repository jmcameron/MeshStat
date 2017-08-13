#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/timer.h>

#include "wxcrafter.h"

#include "Node.h"
#include "NodeDisplay.h"

const std::string MESH_STAT_VERSION = "0.7.0";

typedef enum {
    UNDEFINED = 0,
    STREAM,
    NODE_DISPLAY_PANE
} DISPLAY_MODE;


class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnCredits(wxCommandEvent& event);
    void OnRefresh(wxCommandEvent& event);
    void OnProbeAll(wxTimerEvent& event);

protected:
    virtual void OnTest1(wxCommandEvent& event);

    void refresh();
    void probeAll();

private:
    NodeMap nodes;
    NodeDisplayMap node_displays;
};

#endif // MAINFRAME_H
