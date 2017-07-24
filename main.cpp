#include <wx/wx.h>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/image.h>

#include "MainFrame.h"
#include "CommandLine.h"

extern MeshStatRunInfo run_info;


// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {}
    virtual ~MainApp() {}

    virtual bool OnInit() 
    {
	if (!parseCommandLine(argc, argv, run_info))
	    return false;

        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        MainFrame *mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
