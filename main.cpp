#include <wx/wx.h>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/image.h>
#include <wx/iconbndl.h>

#include "MainFrame.h"
#include "Config.h"


extern ConfigInfo config;

MainFrame *main_frame_global;


// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {}
    virtual ~MainApp() {}

    virtual bool OnInit() 
    {
        if (!config.parseCommandLine(argc, argv))
            return false;

        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        MainFrame *mainFrame = new MainFrame(NULL);
	main_frame_global = mainFrame;
        SetTopWindow(mainFrame);

        // Set up the icons
        wxIconBundle icons;
        icons.AddIcon(wxIcon("icons/mesh_stat_icon_16.png"));
        icons.AddIcon(wxIcon("icons/mesh_stat_icon_32.png"));
        icons.AddIcon(wxIcon("icons/mesh_stat_icon_48.png"));
        icons.AddIcon(wxIcon("icons/mesh_stat_icon_64.png"));
        icons.AddIcon(wxIcon("icons/mesh_stat_icon_128.png"));
        mainFrame->SetIcons(icons);

        GetTopWindow()->Show();

	mainFrame->refresh();
        mainFrame->probeAllNodes();

        return true;
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
