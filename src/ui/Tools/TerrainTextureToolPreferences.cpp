#include "TerrainTextureToolPreferences.h"

TerrainTextureToolPreferences::TerrainTextureToolPreferences(wxWindow *parentPanel) : ToolPreferences(parentPanel){
    this->id = TOOL_PANEL_TERRAIN_TEXTURE;

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxStaticText *text = new wxStaticText(this, wxID_ANY, wxT("Terrain Texture Tool"));
    text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *brushSizeHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushSizeText = new wxStaticText(this, wxID_ANY, wxT("Brush Size:"));
    brushSizeSpin = new wxSpinCtrl(this, TERRAIN_TEXTURE_PREFERENCES_BRUSH_SIZE_SPIN);
    brushSizeSlider = new wxSlider(this, TERRAIN_TEXTURE_PREFERENCES_BRUSH_SIZE_SLIDER, 2, 2, 89);
    brushSizeHorizontal->Add(brushSizeText);
    brushSizeHorizontal->Add(brushSizeSpin, 1, wxLEFT, 10);
    brushSizeHorizontal->Add(brushSizeSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);

    wxBoxSizer *brushFlowHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *brushFlowText = new wxStaticText(this, wxID_ANY, wxT("Brush Flow:"));
    brushFlowSpin = new wxSpinCtrl(this, TERRAIN_TEXTURE_PREFERENCES_BRUSH_FLOW_SPIN);
    brushFlowSlider = new wxSlider(this, TERRAIN_TEXTURE_PREFERENCES_BRUSH_FLOW_SLIDER, 1, 1, 100);
    brushFlowHorizontal->Add(brushFlowText);
    brushFlowHorizontal->Add(brushFlowSpin, 1, wxLEFT, 10);
    brushFlowHorizontal->Add(brushFlowSlider, 1, wxEXPAND | wxRIGHT | wxLEFT, 10);


    wxBitmap bitmap(wxT("../media/img/icon.png"));
    wxBoxSizer *terrainLayersHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxBitmapToggleButton *first = new wxBitmapToggleButton(this, TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FIRST, bitmap);
    wxBitmapToggleButton *second = new wxBitmapToggleButton(this, TERRAIN_TEXTURE_PREFERENCES_TEXTURE_SECOND, bitmap);
    wxBitmapToggleButton *third = new wxBitmapToggleButton(this, TERRAIN_TEXTURE_PREFERENCES_TEXTURE_THIRD, bitmap);
    wxBitmapToggleButton *fourth = new wxBitmapToggleButton(this, TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FOURTH, bitmap);

    textureButtons.push_back(first);
    textureButtons.push_back(second);
    textureButtons.push_back(third);
    textureButtons.push_back(fourth);

    terrainLayersHorizontal->Add(first, 0, wxALL, 5);
    terrainLayersHorizontal->Add(second, 0, wxALL, 5);
    terrainLayersHorizontal->Add(third, 0, wxALL, 5);
    terrainLayersHorizontal->Add(fourth, 0, wxALL, 5);


    vertical->Add(text, 0, wxALL, 10);
    vertical->Add(brushSizeHorizontal, 0, wxEXPAND | wxALL, 10);
    vertical->Add(brushFlowHorizontal, 0, wxEXPAND | wxALL, 10);
    vertical->Add(new wxStaticText(this, wxID_ANY, wxT("Terrain Textures:")), 0, wxALL, 10);
    vertical->Add(terrainLayersHorizontal, 0, wxLEFT, 20);

    brushSizeSpin->SetRange(1, 2000);
    brushFlowSpin->SetRange(1, 100);

    SetSizer(vertical);

    setBrushSize(100);
    setBrushFlow(100);
    setCurrentTerrainTexture(TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FIRST);

    Connect(TERRAIN_TEXTURE_PREFERENCES_BRUSH_SIZE_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainTextureToolPreferences::brushSizeSlideEvent));
    Connect(TERRAIN_TEXTURE_PREFERENCES_BRUSH_SIZE_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainTextureToolPreferences::brushSizeSpinEvent));

    Connect(TERRAIN_TEXTURE_PREFERENCES_BRUSH_FLOW_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TerrainTextureToolPreferences::brushFlowSlideEvent));
    Connect(TERRAIN_TEXTURE_PREFERENCES_BRUSH_FLOW_SPIN, wxEVT_SPINCTRL, wxSpinEventHandler(TerrainTextureToolPreferences::brushFlowSpinEvent));

    Connect(TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FIRST, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(TerrainTextureToolPreferences::textureButtonPressed));
    Connect(TERRAIN_TEXTURE_PREFERENCES_TEXTURE_SECOND, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(TerrainTextureToolPreferences::textureButtonPressed));
    Connect(TERRAIN_TEXTURE_PREFERENCES_TEXTURE_THIRD, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(TerrainTextureToolPreferences::textureButtonPressed));
    Connect(TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FOURTH, wxEVT_TOGGLEBUTTON, wxCommandEventHandler(TerrainTextureToolPreferences::textureButtonPressed));
}

TerrainTextureToolPreferences::~TerrainTextureToolPreferences(){

}

void TerrainTextureToolPreferences::setBrushSize(int brushSize){
    setBrushSizeSpin(brushSize);
}

void TerrainTextureToolPreferences::setBrushFlow(int flow){
    brushFlowSpin->SetValue(flow);
    brushFlowSlider->SetValue(flow);
}

void TerrainTextureToolPreferences::brushSizeSlideEvent(wxScrollEvent &event){
    //Turn the position into degrees so that it can be fed into the tan curve
    float sliderValueDegree = (event.GetPosition() * M_PI) / 180;
    //Put the value into the curve and then divide by the max, to get a number between 0 and 1.
    //Then just multiply that by whatever value you need, so numbers between 2000 in this case
    float tanValue =  std::tan(sliderValueDegree) / 57.2;
    float finalValue = tanValue * 2000;

    brushSizeSpin->SetValue((int)finalValue);

}

void TerrainTextureToolPreferences::brushSizeSpinEvent(wxSpinEvent &event){
    setBrushSizeSpin(event.GetValue());
}

void TerrainTextureToolPreferences::setBrushSizeSpin(int brushSize){
    brushSizeSpin->SetValue(brushSize);
    float tanValue = (float)brushSize / 2000;

    float finalValue = (std::atan(tanValue * 57.2) * 180) / M_PI;

    brushSizeSlider->SetValue(finalValue);
}

void TerrainTextureToolPreferences::brushFlowSlideEvent(wxScrollEvent &event){
    brushFlowSpin->SetValue(event.GetPosition());
}

void TerrainTextureToolPreferences::brushFlowSpinEvent(wxSpinEvent &event){
    brushFlowSlider->SetValue(event.GetValue());
}

float TerrainTextureToolPreferences::getBrushSize(){
    return brushSizeSpin->GetValue();
}

int TerrainTextureToolPreferences::getBrushFlow(){
    return brushFlowSpin->GetValue();
}

void TerrainTextureToolPreferences::textureButtonPressed(wxCommandEvent &event){
    setCurrentTerrainTexture(event.GetId());
}

void TerrainTextureToolPreferences::setCurrentTerrainTexture(int buttonID){
    for(int i = 0; i < textureButtons.size(); i++){
        wxBitmapToggleButton *button = textureButtons.at(i);
        if(button->GetId() == buttonID){
            button->SetValue(true);
        }else{
            button->SetValue(false);
        }
    }
    if(buttonID == TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FIRST) currentTerrainTextureID = 0;
    if(buttonID == TERRAIN_TEXTURE_PREFERENCES_TEXTURE_SECOND) currentTerrainTextureID = 1;
    if(buttonID == TERRAIN_TEXTURE_PREFERENCES_TEXTURE_THIRD) currentTerrainTextureID = 2;
    if(buttonID == TERRAIN_TEXTURE_PREFERENCES_TEXTURE_FOURTH) currentTerrainTextureID = 3;
}

int TerrainTextureToolPreferences::getCurrentTerrainTextureID(){
    return currentTerrainTextureID;
}
