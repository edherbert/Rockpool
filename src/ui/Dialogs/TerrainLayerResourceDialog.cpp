#include "TerrainLayerResourceDialog.h"

TerrainLayerResourceDialog::TerrainLayerResourceDialog(wxWindow *parent, ResourceManager *resManager) : wxDialog(parent, wxID_ANY, wxT("Select Layer Image"), wxDefaultPosition, wxSize(520, 600)){
    this->parent = parent;
    this->resManager = resManager;

    wxScrolledWindow *scrollWindow = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer *scrollWindowSizer = new wxBoxSizer(wxVERTICAL);
    scrollWindow->SetSizer(scrollWindowSizer);

    scrollWindow->SetScrollbars(5, 5, 0, 0);

    resourcePanel = new ResourcePanel(scrollWindow, resManager);
    scrollWindowSizer->Add(resourcePanel, 1, wxEXPAND);

    wxButton *cancelButton = new wxButton(this, TERRAIN_LAYER_DIALOG_CANCEL, wxT("Cancel"));
    wxButton *selectButton = new wxButton(this, TERRAIN_LAYER_DIALOG_SELECT, wxT("Select"));
    //selectButton->Disable();

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    horizontalSizer->Add(new wxPanel(this), 1, wxEXPAND);
    horizontalSizer->Add(cancelButton, 0, wxALL, 10);
    horizontalSizer->Add(selectButton, 0, wxTOP | wxBOTTOM | wxRIGHT, 10);

    resourcePanel->updateTiles();
    resourcePanel->layoutTiles();

    verticalSizer->Add(scrollWindow, 1, wxEXPAND | wxALL, 10);
    verticalSizer->Add(horizontalSizer, 0, wxEXPAND);

    SetSizer(verticalSizer);

    Connect(TERRAIN_LAYER_DIALOG_CANCEL, wxEVT_BUTTON, wxCommandEventHandler(TerrainLayerResourceDialog::cancelButtonPressed));
    Connect(TERRAIN_LAYER_DIALOG_SELECT, wxEVT_BUTTON, wxCommandEventHandler(TerrainLayerResourceDialog::selectButtonPressed));

    ShowModal();
}

TerrainLayerResourceDialog::~TerrainLayerResourceDialog(){

}

void TerrainLayerResourceDialog::cancelButtonPressed(wxCommandEvent &event){
    Destroy();
}

void TerrainLayerResourceDialog::selectButtonPressed(wxCommandEvent &event){
    if(resourcePanel->getCurrentTile()){
        returnValue = resourcePanel->getCurrentTile()->getLabel();
        Destroy();
    }
}

wxString TerrainLayerResourceDialog::getValue(){
    return returnValue;
}
