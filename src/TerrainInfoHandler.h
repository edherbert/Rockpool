#ifndef TERRAININFOHANDLER_H
#define TERRAININFOHANDLER_H

#include "MainFrame.h"
#include "TerrainInfoLayerBox.h"
#include <wx/wx.h>
#include "wxIDs.h"
#include <vector>

class TerrainInfoLayerBox;

class TerrainInfoHandler : wxApp
{
    public:
        TerrainInfoHandler(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~TerrainInfoHandler();

        void setTerrainInfoVisability(bool visible = true);
        void updateInformation();
        void updateLayerBoxes();
        void updateCheckButtons();

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        wxBitmapButton *newLayerButton;
        wxBitmapButton *moveLayerUpButton;
        wxBitmapButton *moveLayerDownButton;
        wxBitmapButton *deleteLayerButton;

        bool terrainInfoVisible = false;
        int maxLayers = 4;

        void newLayerButtonPressed(wxCommandEvent &event);
        void deleteLayerButtonPressed(wxCommandEvent &event);

        struct terrainInformation{
            int layerNum;
            std::string layerName;
        };

        std::vector<TerrainInfoLayerBox*>layerBoxes;
        std::vector<terrainInformation>layerInformation;

};

#endif // TERRAININFOHANDLER_H
