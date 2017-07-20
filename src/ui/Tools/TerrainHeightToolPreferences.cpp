#include "TerrainHeightToolPreferences.h"

TerrainHeightToolPreferences::TerrainHeightToolPreferences(wxWindow *parentPanel) : ToolPreferences(parentPanel){
    this->id = TOOL_PANEL_TERRAIN_HEIGHT;
    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxStaticText *text = new wxStaticText(this, wxID_ANY, wxT("Terrain Height Tool"));
    text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *brushSizeHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushSizeText = new wxStaticText(this, wxID_ANY, wxT("Brush Size:"));
    brushSizeSpin = new wxSpinCtrl(this, TERRAIN_HEIGHT_PREFERENCES_BRUSH_SIZE_SPIN);
    brushSizeSlider = new wxSlider(this, TERRAIN_HEIGHT_PREFERENCES_BRUSH_SIZE_SLIDER, 2, 2, 89);

    wxBoxSizer *terrainHeightHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *terrainHeightText = new wxStaticText(this, wxID_ANY, wxT("Terrain height:"));
    terrainHeightSpin = new wxSpinCtrl(this, wxID_ANY);

    //terrainHeightSpin->SetRange(-600, 600);
    terrainHeightSpin->SetRange(-10000, 10000);

    brushSizeHorizontal->Add(brushSizeText);
    brushSizeHorizontal->Add(brushSizeSpin, 1, wxLEFT, 10);
    brushSizeHorizontal->Add(brushSizeSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);

    terrainHeightHorizontal->Add(terrainHeightText, 0, wxLEFT | wxRIGHT, 10);
    terrainHeightHorizontal->Add(terrainHeightSpin);

    vertical->Add(text, 0, wxALL, 10);
    vertical->Add(brushSizeHorizontal, 0, wxEXPAND | wxALL, 10);
    vertical->Add(terrainHeightHorizontal);

    brushSizeSpin->SetRange(1, 2000);

    Connect(TERRAIN_HEIGHT_PREFERENCES_BRUSH_SIZE_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainHeightToolPreferences::brushSizeSlideEvent));
    Connect(TERRAIN_HEIGHT_PREFERENCES_BRUSH_SIZE_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainHeightToolPreferences::brushSizeSpinEvent));

    SetSizer(vertical);
}

TerrainHeightToolPreferences::~TerrainHeightToolPreferences(){

}

void TerrainHeightToolPreferences::setBrushSize(int brushSize){
    setBrushSizeSpin(brushSize);
}

int TerrainHeightToolPreferences::getHeight(){
    return terrainHeightSpin->GetValue();
}

void TerrainHeightToolPreferences::brushSizeSlideEvent(wxScrollEvent &event){
    //Turn the position into degrees so that it can be fed into the tan curve
    float sliderValueDegree = (event.GetPosition() * M_PI) / 180;
    //Put the value into the curve and then divide by the max, to get a number between 0 and 1.
    //Then just multiply that by whatever value you need, so numbers between 2000 in this case
    float tanValue =  std::tan(sliderValueDegree) / 57.2;
    float finalValue = tanValue * 2000;

    brushSizeSpin->SetValue((int)finalValue);

}

void TerrainHeightToolPreferences::brushSizeSpinEvent(wxSpinEvent &event){
    setBrushSizeSpin(event.GetValue());
}

void TerrainHeightToolPreferences::setBrushSizeSpin(int brushSize){
    brushSizeSpin->SetValue(brushSize);
    float tanValue = (float)brushSize / 2000;

    float finalValue = (std::atan(tanValue * 57.2) * 180) / M_PI;

    brushSizeSlider->SetValue(finalValue);
}

float TerrainHeightToolPreferences::getBrushSize(){
    return brushSizeSpin->GetValue();
}
