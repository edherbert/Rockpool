#ifndef RESOURCEBROWSER_H
#define RESOURCEBROWSER_H

#include <wx/wx.h>

#include "../MainFrame.h"
#include "ResourcePanel.h"
#include <wx/srchctrl.h>

class MainFrame;
class ResourcePanel;

class ResourceBrowser : public wxPanel
{
    public:
        ResourceBrowser(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ResourceBrowser();

        void setResourceBrowserVisability(bool visible);

        void updateTiles();
        void layoutTiles();

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        ResourcePanel *resPanel;

        bool browserVisible = false;
};

#endif // RESOURCEBROWSER_H
