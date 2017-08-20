#ifndef TOOLSPANELHANDLER_H
#define TOOLSPANELHANDLER_H

#include <wx/aui/aui.h>
#include "../MainFrame.h"
#include <wx/app.h>

class MainFrame;

class ToolsPanelHandler : wxApp
{
    public:
        ToolsPanelHandler(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ToolsPanelHandler();

        void setTool(int toolId);
        void setToolPanelVisibility(bool val);

        int getCurrentTool();

    protected:

    private:
        wxAuiManager *auiManager;
        wxAuiToolBar *toolbar;
        MainFrame *mainFrame;

        int tools[4];
        int currentTool = 0;

        void terrainEditToolCallback(wxCommandEvent &event);
        void terrainTextureToolCallback(wxCommandEvent &event);
        void terrainHeightToolCallback(wxCommandEvent &event);
        void terrainSmoothToolCallback(wxCommandEvent &event);
};

#endif // TOOLSPANELHANDLER_H
