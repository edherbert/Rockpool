#ifndef TERRAINTEXTURETOOLPREFERENCES_H
#define TERRAINTEXTURETOOLPREFERENCES_H

#include <wx/wx.h>
#include "ToolPreferences.h"
#include <vector>

#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/tglbtn.h>

class TerrainTextureToolPreferences : public ToolPreferences
{
    public:
        TerrainTextureToolPreferences(wxWindow *parentPanel);
        virtual ~TerrainTextureToolPreferences();

        void setBrushSize(int brushSize);
        void setBrushFlow(int flow);

        float getBrushSize();
        int getBrushFlow();
        int getCurrentTerrainTextureID();

        void setCurrentTerrainTexture(int buttonID);

    protected:

    private:
        wxSpinCtrl *brushSizeSpin;
        wxSlider *brushSizeSlider;

        wxSlider *brushFlowSlider;
        wxSpinCtrl *brushFlowSpin;

        void brushSizeSlideEvent(wxScrollEvent &event);
        void brushSizeSpinEvent(wxSpinEvent &event);

        void brushFlowSlideEvent(wxScrollEvent &event);
        void brushFlowSpinEvent(wxSpinEvent &event);

        void setBrushSizeSpin(int brushSize);

        void textureButtonPressed(wxCommandEvent &event);

        int currentTerrainTextureID = 0;

        std::vector<wxBitmapToggleButton*>textureButtons;
};

#endif // TERRAINTEXTURETOOLPREFERENCES_H
