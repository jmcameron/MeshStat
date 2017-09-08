#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/timer.h>

#include "wxcrafter.h"

#include "Node.h"
#include "NodeDisplay.h"

const std::string MESH_STAT_VERSION = "0.9.5";


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

    void refresh();
    void probeAllNodes();

protected:
    virtual void OnTest1(wxCommandEvent& event);

private:
    NodeMap nodes;
    NodeDisplayMap node_displays;
    bool close_requested;
    bool probing;
};

#endif // MAINFRAME_H
