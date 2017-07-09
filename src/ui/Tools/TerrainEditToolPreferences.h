#ifndef TERRAINEDITTOOLPREFERENCES_H
#define TERRAINEDITTOOLPREFERENCES_H

#include <wx/wx.h>
#include "ToolPreferences.h"
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include "../wxIDs.h"
#include <cmath>

class ToolPreferences;

class TerrainEditToolPreferences : public ToolPreferences
{
    public:
        TerrainEditToolPreferences(wxWindow *parentPanel);
        virtual ~TerrainEditToolPreferences();

        void setBrushSize(int brushSize);
        void setBrushFlow(int flow);

        float getBrushSize();
        int getBrushFlow();

    protected:

    private:
        void brushSizeSlideEvent(wxScrollEvent &event);
        void brushSizeSpinEvent(wxSpinEvent &event);

        void brushFlowSlideEvent(wxScrollEvent &event);
        void brushFlowSpinEvent(wxSpinEvent &event);

        //For calling without the event
        void setBrushSizeSpin(int brushSize);

        wxSpinCtrl *brushSizeSpin;
        wxSlider *brushSizeSlider;

        wxSlider *brushFlowSlider;
        wxSpinCtrl *brushFlowSpin;
};

#endif // TERRAINEDITTOOLPREFERENCES_H
