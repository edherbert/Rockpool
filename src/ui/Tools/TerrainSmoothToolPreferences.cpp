#include "TerrainSmoothToolPreferences.h"

TerrainSmoothToolPreferences::TerrainSmoothToolPreferences(wxWindow *parentPanel) : ToolPreferences(parentPanel){
    this->id = TOOL_PANEL_TERRAIN_SMOOTH;

     wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxStaticText *text = new wxStaticText(this, wxID_ANY, wxT("Terrain Smooth Tool"));
    text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *brushSizeHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushSizeText = new wxStaticText(this, wxID_ANY, wxT("Brush Size:"));
    brushSizeSpin = new wxSpinCtrl(this, TERRAIN_SMOOTH_PREFERENCES_BRUSH_SIZE_SPIN);
    brushSizeSlider = new wxSlider(this, TERRAIN_SMOOTH_PREFERENCES_BRUSH_SIZE_SLIDER, 2, 2, 89);
    brushSizeHorizontal->Add(brushSizeText);
    brushSizeHorizontal->Add(brushSizeSpin, 1, wxLEFT, 10);
    brushSizeHorizontal->Add(brushSizeSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);

    wxBoxSizer *brushFlowHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushFlowText = new wxStaticText(this, wxID_ANY, wxT("Brush Flow:"));
    brushFlowSpin = new wxSpinCtrl(this, TERRAIN_SMOOTH_PREFERENCES_BRUSH_FLOW_SPIN);
    brushFlowSlider = new wxSlider(this, TERRAIN_SMOOTH_PREFERENCES_BRUSH_FLOW_SLIDER, 1, 1, 100);
    brushFlowHorizontal->Add(brushFlowText);
    brushFlowHorizontal->Add(brushFlowSpin, 1, wxLEFT, 10);
    brushFlowHorizontal->Add(brushFlowSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);


    vertical->Add(text, 0, wxALL, 10);
    vertical->Add(brushSizeHorizontal, 0, wxEXPAND | wxALL, 10);
    vertical->Add(brushFlowHorizontal, 0, wxEXPAND | wxALL, 10);

    brushSizeSpin->SetRange(1, 2000);
    brushFlowSpin->SetRange(1, 100);

    this->SetSizer(vertical);

    Connect(TERRAIN_SMOOTH_PREFERENCES_BRUSH_SIZE_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainSmoothToolPreferences::brushSizeSlideEvent));
    Connect(TERRAIN_SMOOTH_PREFERENCES_BRUSH_SIZE_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainSmoothToolPreferences::brushSizeSpinEvent));

    Connect(TERRAIN_SMOOTH_PREFERENCES_BRUSH_FLOW_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainSmoothToolPreferences::brushFlowSlideEvent));
    Connect(TERRAIN_SMOOTH_PREFERENCES_BRUSH_FLOW_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainSmoothToolPreferences::brushFlowSpinEvent));
}

TerrainSmoothToolPreferences::~TerrainSmoothToolPreferences(){

}

void TerrainSmoothToolPreferences::setBrushSize(int brushSize){
    setBrushSizeSpin(brushSize);
}

void TerrainSmoothToolPreferences::setBrushFlow(int flow){
    brushFlowSpin->SetValue(flow);
    brushFlowSlider->SetValue(flow);
}

void TerrainSmoothToolPreferences::brushSizeSlideEvent(wxScrollEvent &event){
    float sliderValueDegree = (event.GetPosition() * M_PI) / 180;
    float tanValue =  std::tan(sliderValueDegree) / 57.2;
    float finalValue = tanValue * 2000;

    brushSizeSpin->SetValue((int)finalValue);

}

void TerrainSmoothToolPreferences::brushSizeSpinEvent(wxSpinEvent &event){
    setBrushSizeSpin(event.GetValue());
}

void TerrainSmoothToolPreferences::setBrushSizeSpin(int brushSize){
    brushSizeSpin->SetValue(brushSize);
    float tanValue = (float)brushSize / 2000;

    float finalValue = (std::atan(tanValue * 57.2) * 180) / M_PI;

    brushSizeSlider->SetValue(finalValue);
}

void TerrainSmoothToolPreferences::brushFlowSlideEvent(wxScrollEvent &event){
    brushFlowSpin->SetValue(event.GetPosition());
}

void TerrainSmoothToolPreferences::brushFlowSpinEvent(wxSpinEvent &event){
    brushFlowSlider->SetValue(event.GetValue());
}

float TerrainSmoothToolPreferences::getBrushSize(){
    return brushSizeSpin->GetValue();
}

int TerrainSmoothToolPreferences::getBrushFlow(){
    return brushFlowSpin->GetValue();
}
