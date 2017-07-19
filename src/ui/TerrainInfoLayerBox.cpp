#include "TerrainInfoLayerBox.h"

TerrainInfoLayerBox::TerrainInfoLayerBox(wxWindow *parent, wxBoxSizer *parentSizer, TerrainInfoHandler *handler) : wxPanel(parent, wxID_ANY){
    //SetBackgroundColour(wxColour("#0000FF"));
    this->parentSizer = parentSizer;
    this->handler = handler;

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(verticalSizer);

    wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);

    layerSelectedCheckBox = new wxCheckBox(this, TERRAIN_INFO_LAYER_CHECK_BOX, wxEmptyString);

    wxPanel *layerSettingsPanel = new wxPanel(this);
    //layerSettingsPanel->SetBackgroundColour(wxColour("#FF0000"));
    wxBoxSizer *layerSettingsPanelSizer = new wxBoxSizer(wxVERTICAL);
    layerSettingsPanel->SetSizer(layerSettingsPanelSizer);


    wxStaticBitmap *textureBitmap = new wxStaticBitmap(layerSettingsPanel, wxID_ANY, wxBitmap(wxT("../media/img/icon.png")));

    textureSrcText = new wxStaticText(layerSettingsPanel, wxID_ANY, wxEmptyString);
    textureSrcButton = new wxButton(layerSettingsPanel, TERRAIN_INFO_LAYER_IMAGE_SELECT_BUTTON, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);

    wxBoxSizer *textureSrcHorizontal = new wxBoxSizer(wxHORIZONTAL);
    textureSrcHorizontal->Add(textureSrcText, 1, wxEXPAND);
    textureSrcHorizontal->Add(textureSrcButton);

    layerSettingsPanelSizer->Add(textureBitmap, 0);
    layerSettingsPanelSizer->Add(textureSrcHorizontal, 0, wxEXPAND);


    horizontalSizer->Add(layerSelectedCheckBox, 0, wxALL, 5);
    horizontalSizer->Add(new wxStaticLine(this, wxID_ANY,  wxDefaultPosition, wxDefaultSize, wxVERTICAL), 0, wxEXPAND);
    horizontalSizer->Add(layerSettingsPanel, 1, wxEXPAND | wxALL, 5);

    verticalSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxTOP, 5);
    verticalSizer->Add(horizontalSizer, 1, wxEXPAND);
    verticalSizer->Add(new wxStaticLine(this), 0, wxEXPAND);

    parentSizer->Add(this, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    Connect(TERRAIN_INFO_LAYER_CHECK_BOX, wxEVT_CHECKBOX, wxCommandEventHandler(TerrainInfoLayerBox::layerChecked));
    Connect(TERRAIN_INFO_LAYER_IMAGE_SELECT_BUTTON, wxEVT_BUTTON, wxCommandEventHandler(TerrainInfoLayerBox::imageSelectButtonPressed));
}

TerrainInfoLayerBox::~TerrainInfoLayerBox(){

}

void TerrainInfoLayerBox::layerChecked(wxCommandEvent &event){
    checked = event.IsChecked();
    handler->updateCheckButtons();
}

bool TerrainInfoLayerBox::isChecked(){
    return checked;
}

void TerrainInfoLayerBox::setChecked(bool value){
    layerSelectedCheckBox->SetValue(value);
    checked = value;
}

void TerrainInfoLayerBox::setInfo(std::string name){
    textureSrcText->SetLabel((wxString)name);
}

std::string TerrainInfoLayerBox::getInfo(){
    return (std::string)textureSrcText->GetLabel();
}

void TerrainInfoLayerBox::imageSelectButtonPressed(wxCommandEvent &event){
    TerrainLayerResourceDialog dialog(this, handler->getMainFrame()->getResourceManager());
    if(dialog.getValue() != wxEmptyString){
        textureSrcText->SetLabel(dialog.getValue());

        handler->refreshTerrain();
        Ogre::Root::getSingleton().renderOneFrame();
    }
}
