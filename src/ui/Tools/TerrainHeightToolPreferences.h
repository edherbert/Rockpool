#ifndef TERRAINHEIGHTTOOLPREFERENCES_H
#define TERRAINHEIGHTTOOLPREFERENCES_H

#include <wx/wx.h>
#include "ToolPreferences.h"
#include <wx/spinctrl.h>
#include <wx/slider.h>

class TerrainHeightToolPreferences : public ToolPreferences
{
    public:
        TerrainHeightToolPreferences(wxWindow *parentPanel);
        virtual ~TerrainHeightToolPreferences();

        void setBrushSize(int brushSize);
        float getBrushSize();
        int getHeight();

    protected:

    private:
        void brushSizeSlideEvent(wxScrollEvent &event);
        void brushSizeSpinEvent(wxSpinEvent &event);

        void setBrushSizeSpin(int brushSize);

        wxSpinCtrl *terrainHeightSpin;

        wxSpinCtrl *brushSizeSpin;
        wxSlider *brushSizeSlider;
};

#endif // TERRAINHEIGHTTOOLPREFERENCES_H
