#ifndef TOOLPREFERENCESHANDLER_H
#define TOOLPREFERENCESHANDLER_H

#include "../MainFrame.h"
#include "wx/wx.h"
#include <wx/aui/aui.h>

#include "TerrainEditToolPreferences.h"
#include "TerrainTextureToolPreferences.h"
#include "TerrainHeightToolPreferences.h"
#include "ToolPreferences.h"

#include <vector>

class MainFrame;

class ToolPreferencesHandler
{
    public:
        ToolPreferencesHandler(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ToolPreferencesHandler();

        void setToolPreference(int toolID);
        ToolPreferences* getToolById(int id);

        TerrainEditToolPreferences* getTerrainEditTool();
        TerrainTextureToolPreferences* getTerrainTextureTool();
        TerrainHeightToolPreferences* getTerrainHeightTool();

        void setToolPreferencesVisability(bool visible = true);

        //Store them as individual items as well as in the vector
        TerrainEditToolPreferences *editPreferences;
        TerrainTextureToolPreferences *texturePreferences;
        TerrainHeightToolPreferences *terrainHeightPreferences;

    protected:

    private:
        MainFrame *mainFrame;
        wxPanel *parentPanel;
        wxAuiManager *auiManager;

        bool toolPreferencesVisible = false;

        std::vector<ToolPreferences*>preferences;
};

#endif // TOOLPREFERENCES_H
