//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef TEST3_MYTEST3_WXCRAFTER_BASE_CLASSES_H
#define TEST3_MYTEST3_WXCRAFTER_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/timer.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/frame.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

class MainFrameBaseClass : public wxFrame
{
public:
    enum {
        wxID_MainText = 10001,
        wxID_TEST1   = 10002,
	wxID_CREDITS = 10003,
	wxID_REFRESH = 10004,
	wxID_TIMER   = 10005,
    };

protected:
    // ??? wxTextCtrl* m_MainText;
    wxMenuBar* m_menuBar;

    wxMenu* m_menu_File;
    wxMenuItem* m_menuItem_Exit;

    wxMenu* m_menu_Test;
    wxMenuItem* m_menuItem_Test1;
    wxMenuItem* m_menuItem_Refresh;

    wxMenu* m_menu_Help;
    wxMenuItem* m_menuItem_Credits;
    wxMenuItem* m_menuItem_About;

    // ??? wxToolBar* m_mainToolbar;

    wxTimer *m_timer;

protected:
    virtual void OnExit(wxCommandEvent& event) { event.Skip(); }
    virtual void OnClose(wxCloseEvent& event) { event.Skip(); }
    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }
    virtual void OnTest1(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCredits(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRefresh(wxCommandEvent& event) { event.Skip(); }
    virtual void OnProbeAll(wxTimerEvent& event) { event.Skip(); }

public:
    // ??? wxTextCtrl* GetMainText() { return m_MainText; }
    wxMenuBar* GetMenuBar() { return m_menuBar; }
    // ??? wxToolBar* GetMainToolbar() { return m_mainToolbar; }
    MainFrameBaseClass(wxWindow* parent, 
		       wxWindowID id = wxID_ANY, 
		       const wxString& title = _("MeshStat"), 
		       const wxPoint& pos = wxDefaultPosition, 
		       const wxSize& size = wxSize(10,10), 
		       long style = wxCAPTION|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLOSE_BOX);
    virtual ~MainFrameBaseClass();
};


#endif
