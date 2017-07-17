#ifndef RESOURCEBROWSER_H
#define RESOURCEBROWSER_H

#include <wx/wx.h>

#include "MainFrame.h"
#include <wx/srchctrl.h>

class MainFrame;

class ResourceBrowser : public wxPanel
{
    public:
        ResourceBrowser(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ResourceBrowser();

        void setResourceBrowserVisability(bool visible);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        bool browserVisible = false;
};

#endif // RESOURCEBROWSER_H
