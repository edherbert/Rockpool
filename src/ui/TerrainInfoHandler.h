#ifndef TERRAININFOHANDLER_H
#define TERRAININFOHANDLER_H

#include <wx/aui/aui.h>
#include "MainFrame.h"
#include "TerrainInfoLayerBox.h"
#include <wx/wx.h>
#include "wxIDs.h"
#include <vector>

#include <Ogre.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class TerrainInfoLayerBox;
class MainFrame;

struct terrainInformation{
    int layerNum;
    std::string layerName;
    bool shouldRemove = false;
};

class TerrainInfoHandler : public wxPanel
{
    public:
        TerrainInfoHandler(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~TerrainInfoHandler();

        void setTerrainInfoVisability(bool visible = true);
        void updateLayerBoxes();
        void updateCheckButtons();
        void updateTerrainInformation();

        void setTerrainTextureName(int id, wxString value);

        void refreshTerrain();

        MainFrame* getMainFrame();

        void setCurrentTerrain(Ogre::Terrain *terrain);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        wxBitmapButton *newLayerButton;
        wxBitmapButton *moveLayerUpButton;
        wxBitmapButton *moveLayerDownButton;
        wxBitmapButton *deleteLayerButton;

        wxStaticText *noTerrainText;
        wxPanel *contentPanel;
        wxStaticText *terrainPositionText;
        wxTextCtrl *terrainNameCtrl;

        Ogre::Terrain *currentTerrain;

        bool terrainInfoVisible = false;
        int maxLayers = 4;

        void newLayerButtonPressed(wxCommandEvent &event);
        void deleteLayerButtonPressed(wxCommandEvent &event);

        std::vector<TerrainInfoLayerBox*>layerBoxes;
        std::vector<terrainInformation>layerInformation;

};

#endif // TERRAININFOHANDLER_H
