#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"

const std::string MESH_STAT_VERSION = "0.1.0";


class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnTest1(wxCommandEvent& event);
};
#endif // MAINFRAME_H
