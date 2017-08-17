//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include <wx/wx.h>
#include <wx/event.h>

#include "wxcrafter.h"


// Declare the bitmap loading function
extern void wxC9ED9InitBitmapResources();

static bool bBitmapLoaded = false;


MainFrameBaseClass::MainFrameBaseClass(wxWindow* parent, 
				       wxWindowID id, 
				       const wxString& title, 
				       const wxPoint& pos, 
				       const wxSize& size, 
				       long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }
    
    SetBackgroundColour(wxColour(* wxWHITE)); 
   
    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);
    
    m_menu_File = new wxMenu();
    m_menuBar->Append(m_menu_File, _("File"));
    
    m_menuItem_Exit = new wxMenuItem(m_menu_File, wxID_EXIT, _("Exit\tAlt-X"), _("Quit"), wxITEM_NORMAL);
    m_menu_File->Append(m_menuItem_Exit);
    
    m_menu_Test = new wxMenu();
    m_menuBar->Append(m_menu_Test, _("Test"));
    
    m_menuItem_Test1 = new wxMenuItem(m_menu_Test, wxID_TEST1, _("Test1"), wxT(""), wxITEM_NORMAL);
    m_menu_Test->Append(m_menuItem_Test1);
    
    m_menuItem_Refresh = new wxMenuItem(m_menu_Test, wxID_REFRESH, _("Refresh"), wxT(""), wxITEM_NORMAL);
    m_menu_Test->Append(m_menuItem_Refresh);
    
    m_menu_Help = new wxMenu();
    m_menuBar->Append(m_menu_Help, _("Help"));
    
    m_menuItem_Credits = new wxMenuItem(m_menu_Help, wxID_CREDITS, _("Credits"), wxT(""), wxITEM_NORMAL);
    m_menu_Help->Append(m_menuItem_Credits);
    
    m_menuItem_About = new wxMenuItem(m_menu_Help, wxID_ABOUT, _("About..."), wxT(""), wxITEM_NORMAL);
    m_menu_Help->Append(m_menuItem_About);
    
    // ??? m_mainToolbar = this->CreateToolBar(wxTB_FLAT, wxID_ANY);
    // ??? m_mainToolbar->SetToolBitmapSize(wxSize(16,16));

    m_timer = new wxTimer(this, wxID_TIMER);

    SetName(wxT("MainFrameBaseClass"));
    // SetSize(500,300);

    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif

    // Connect events
    this->Connect(m_menuItem_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Connect(m_menuItem_Test1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnTest1), NULL, this);
    this->Connect(m_menuItem_About->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
    this->Connect(m_menuItem_Credits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnCredits), NULL, this);
    this->Connect(m_menuItem_Refresh->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRefresh), NULL, this);
    
    this->Connect(m_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler( MainFrameBaseClass::OnProbeAll ), NULL, this );
    this->Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBaseClass::OnClose), NULL, this);
}

MainFrameBaseClass::~MainFrameBaseClass()
{
    this->Disconnect(m_menuItem_Exit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Disconnect(m_menuItem_Test1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnTest1), NULL, this);
    this->Disconnect(m_menuItem_About->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
    this->Disconnect(m_menuItem_Credits->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnCredits), NULL, this);
    this->Disconnect(m_menuItem_Refresh->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrameBaseClass::OnRefresh), NULL, this);

    this->Disconnect(wxID_TIMER, wxEVT_TIMER, wxTimerEventHandler( MainFrameBaseClass::OnProbeAll ), NULL, this );
    this->Disconnect(wxID_ANY, wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBaseClass::OnClose), NULL, this);
}
