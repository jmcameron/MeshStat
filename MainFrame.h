#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/timer.h>

#include "wxcrafter.h"

#include "Node.h"
#include "NodeDisplay.h"

const std::string MESH_STAT_VERSION = "0.9.0";

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

    virtual void OnExit(wxCommandEvent& event);
    virtual void OnClose(wxCloseEvent& event);
    virtual void OnAbout(wxCommandEvent& event);
    virtual void OnCredits(wxCommandEvent& event);
    virtual void OnRefresh(wxCommandEvent& event);
    virtual void OnProbeAll(wxTimerEvent& event);

protected:
    virtual void OnTest1(wxCommandEvent& event);

    void refresh();
    void probeAllNodes();

private:
    NodeMap nodes;
    NodeDisplayMap node_displays;
    bool close_requested;
    bool probing;
};

#endif // MAINFRAME_H
