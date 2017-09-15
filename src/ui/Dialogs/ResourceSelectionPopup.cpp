#include "ResourceSelectionPopup.h"

#include "../../ui/wxIDs.h"
#include "../Resource/ResourceTile.h"

ResourceSelectionPopup::ResourceSelectionPopup(wxWindow *parent, MainFrame *mainFrame, ResourceManager *resManager) : wxDialog(parent, wxID_ANY, wxT("Select Layer Image"), wxDefaultPosition, wxSize(520, 600)){
    this->parent = parent;
    this->resManager = resManager;

    wxScrolledWindow *scrollWindow = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer *scrollWindowSizer = new wxBoxSizer(wxVERTICAL);
    scrollWindow->SetSizer(scrollWindowSizer);

    resourcePanel = new ResourcePanel(scrollWindow, mainFrame, resManager);
    scrollWindowSizer->Add(resourcePanel, 1, wxEXPAND);

    wxButton *cancelButton = new wxButton(this, RESOURCE_SELECT_DIALOG_CANCEL, wxT("Cancel"));
    wxButton *selectButton = new wxButton(this, RESOURCE_SELECT_DIALOG_SELECT, wxT("Select"));

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

    Connect(RESOURCE_SELECT_DIALOG_CANCEL, wxEVT_BUTTON, wxCommandEventHandler(ResourceSelectionPopup::cancelButtonPressed));
    Connect(RESOURCE_SELECT_DIALOG_SELECT, wxEVT_BUTTON, wxCommandEventHandler(ResourceSelectionPopup::selectButtonPressed));

    ShowModal();
}

ResourceSelectionPopup::~ResourceSelectionPopup(){

}

void ResourceSelectionPopup::cancelButtonPressed(wxCommandEvent &event){
    Destroy();
}

void ResourceSelectionPopup::selectButtonPressed(wxCommandEvent &event){
    if(resourcePanel->getCurrentTile()){
        returnValue = resourcePanel->getCurrentTile()->getValue();
        Destroy();
    }
}

wxString ResourceSelectionPopup::getValue(){
    return returnValue;
}
