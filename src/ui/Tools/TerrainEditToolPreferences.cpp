#include "TerrainEditToolPreferences.h"

TerrainEditToolPreferences::TerrainEditToolPreferences(wxWindow *parentPanel) : ToolPreferences(parentPanel){
    this->id = TOOL_PANEL_TERRAIN_EDIT;

    //Each preferences window has it's own panel

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    //wxBoxSizer *titleHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *text = new wxStaticText(this, wxID_ANY, wxT("Terrain Edit Tool"));
    text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    //titleHorizontal->Add(text, 1, wxALL, 10);

    wxBoxSizer *brushSizeHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushSizeText = new wxStaticText(this, wxID_ANY, wxT("Brush Size:"));
    brushSizeSpin = new wxSpinCtrl(this, TERRAIN_EDIT_PREFERENCES_BRUSH_SIZE_SPIN);
    brushSizeSlider = new wxSlider(this, TERRAIN_EDIT_PREFERENCES_BRUSH_SIZE_SLIDER, 2, 2, 89);
    brushSizeHorizontal->Add(brushSizeText);
    brushSizeHorizontal->Add(brushSizeSpin, 1, wxLEFT, 10);
    brushSizeHorizontal->Add(brushSizeSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);

    wxBoxSizer *brushFlowHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushFlowText = new wxStaticText(this, wxID_ANY, wxT("Brush Flow:"));
    brushFlowSpin = new wxSpinCtrl(this, TERRAIN_EDIT_PREFERENCES_BRUSH_FLOW_SPIN);
    brushFlowSlider = new wxSlider(this, TERRAIN_EDIT_PREFERENCES_BRUSH_FLOW_SLIDER, 1, 1, 100);
    brushFlowHorizontal->Add(brushFlowText);
    brushFlowHorizontal->Add(brushFlowSpin, 1, wxLEFT, 10);
    brushFlowHorizontal->Add(brushFlowSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);


    vertical->Add(text, 0, wxALL, 10);
    vertical->Add(brushSizeHorizontal, 0, wxEXPAND | wxALL, 10);
    vertical->Add(brushFlowHorizontal, 0, wxEXPAND | wxALL, 10);

    brushSizeSpin->SetRange(1, 2000);
    brushFlowSpin->SetRange(1, 100);

    this->SetSizer(vertical);

    Connect(TERRAIN_EDIT_PREFERENCES_BRUSH_SIZE_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainEditToolPreferences::brushSizeSlideEvent));
    Connect(TERRAIN_EDIT_PREFERENCES_BRUSH_SIZE_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainEditToolPreferences::brushSizeSpinEvent));

    Connect(TERRAIN_EDIT_PREFERENCES_BRUSH_FLOW_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainEditToolPreferences::brushFlowSlideEvent));
    Connect(TERRAIN_EDIT_PREFERENCES_BRUSH_FLOW_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainEditToolPreferences::brushFlowSpinEvent));

    setBrushSize(100);
    setBrushFlow(50);
}

TerrainEditToolPreferences::~TerrainEditToolPreferences(){

}

void TerrainEditToolPreferences::setBrushSize(int brushSize){
    setBrushSizeSpin(brushSize);
}

void TerrainEditToolPreferences::setBrushFlow(int flow){
    brushFlowSpin->SetValue(flow);
    brushFlowSlider->SetValue(flow);
}

void TerrainEditToolPreferences::brushSizeSlideEvent(wxScrollEvent &event){
    //Turn the position into degrees so that it can be fed into the tan curve
    float sliderValueDegree = (event.GetPosition() * M_PI) / 180;
    //Put the value into the curve and then divide by the max, to get a number between 0 and 1.
    //Then just multiply that by whatever value you need, so numbers between 2000 in this case
    float tanValue =  std::tan(sliderValueDegree) / 57.2;
    float finalValue = tanValue * 2000;

    brushSizeSpin->SetValue((int)finalValue);

}

void TerrainEditToolPreferences::brushSizeSpinEvent(wxSpinEvent &event){
    setBrushSizeSpin(event.GetValue());
}

void TerrainEditToolPreferences::setBrushSizeSpin(int brushSize){
    brushSizeSpin->SetValue(brushSize);
    float tanValue = (float)brushSize / 2000;

    float finalValue = (std::atan(tanValue * 57.2) * 180) / M_PI;

    brushSizeSlider->SetValue(finalValue);
}

void TerrainEditToolPreferences::brushFlowSlideEvent(wxScrollEvent &event){
    brushFlowSpin->SetValue(event.GetPosition());
}

void TerrainEditToolPreferences::brushFlowSpinEvent(wxSpinEvent &event){
    brushFlowSlider->SetValue(event.GetValue());
}

float TerrainEditToolPreferences::getBrushSize(){
    return brushSizeSpin->GetValue();
}

int TerrainEditToolPreferences::getBrushFlow(){
    return brushFlowSpin->GetValue();
}
