#include "MapPropertiesSkyBoxDialog.h"

#include <wx/wx.h>
#include "MapPropertiesDialog.h"
#include "ResourceSelectionPopup.h"
#include "../../system/SkyBoxManager.h"
#include "../../map/SkyBox.h"

MapPropertiesSkyBoxDialog::MapPropertiesSkyBoxDialog(MapPropertiesDialog *parentDialog, SkyBox *editedSkyBox) : wxDialog(parentDialog, wxID_ANY, wxT("SkyBox Properties"), wxDefaultPosition, wxSize(500, 500)){
    this->parentDialog = parentDialog;
    this->editedSkyBox = editedSkyBox;

    tempSkyBox = new SkyBox();
    if(editedSkyBox){
        tempSkyBox->copyValuesFrom(editedSkyBox);
    }

    wxBoxSizer *skyBoxDialogMainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(skyBoxDialogMainSizer);

    wxBoxSizer *skyBoxNameHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *skyBoxNameStaticText = new wxStaticText(this, wxID_ANY, wxT("SkyBox Name"));
    skyBoxNameTextCtrl = new wxTextCtrl(this, wxID_ANY);

    skyBoxNameHorizontalSizer->Add(skyBoxNameStaticText, 0, wxALL, 10);
    skyBoxNameHorizontalSizer->Add(skyBoxNameTextCtrl, 1, wxRIGHT | wxTOP | wxBOTTOM, 10);

    wxGridSizer *skyBoxGridSizer = new wxGridSizer(2, 3, 5, 5);

    wxColour blue("#0000FF");
    wxBitmap iconImage(wxT("../media/img/icon.png"));
    for(int i = 0; i < 6; i++){
        wxPanel *content = new wxPanel(this);

        wxBoxSizer *contentVertical = new wxBoxSizer(wxVERTICAL);

        //wxStaticBitmap *icon = new wxStaticBitmap(content, wxID_ANY, iconImage);
        wxBitmapButton *icon = new wxBitmapButton(content, buttonIDs[i], iconImage);
        wxStaticText *directionName = new wxStaticText(content, wxID_ANY, "");
        pathStrings[i] = directionName;

        wxStaticText *directionLabel = new wxStaticText(content, wxID_ANY, skyBoxImageNames[i]);

        contentVertical->Add(icon, 1, wxEXPAND);
        contentVertical->Add(directionName, 0, wxALIGN_CENTRE_HORIZONTAL);
        contentVertical->Add(directionLabel, 0, wxALIGN_CENTRE_HORIZONTAL);

        content->SetSizer(contentVertical);
        skyBoxGridSizer->Add(content, 1, wxEXPAND);

        Connect(buttonIDs[i], wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesSkyBoxDialog::imageButtonPressed));
    }

    wxBoxSizer *skyBoxHorizontalButtons = new wxBoxSizer(wxHORIZONTAL);
    wxButton *cancelButton = new wxButton(this, DIALOG_SKYBOX_CANCEL, wxT("Cancel"));
    wxButton *OkButton = new wxButton(this, DIALOG_SKYBOX_OK, wxT("OK"));

    //Just to make sure that the text box isn't selected when it starts (that's quite annoying).
    OkButton->SetFocus();

    skyBoxHorizontalButtons->Add(cancelButton, 0, wxALL, 10);
    skyBoxHorizontalButtons->Add(new wxPanel(this), 1, wxEXPAND);
    skyBoxHorizontalButtons->Add(OkButton, 0, wxALL, 10);

    skyBoxDialogMainSizer->Add(skyBoxNameHorizontalSizer, 0, wxEXPAND);
    skyBoxDialogMainSizer->Add(skyBoxGridSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
    skyBoxDialogMainSizer->Add(skyBoxHorizontalButtons, 0, wxEXPAND);

    //populate the dialog with the values for the temp sky box.
    skyBoxNameTextCtrl->SetValue(tempSkyBox->getName());
    for(int i = 0; i < 6; i++){
        pathStrings[i]->SetLabel(tempSkyBox->getSkyBoxValue(i));
    }

    Connect(DIALOG_SKYBOX_CANCEL, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesSkyBoxDialog::cancelButtonPressed));
    Connect(DIALOG_SKYBOX_OK, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesSkyBoxDialog::okButtonPressed));

    ShowModal();
}

MapPropertiesSkyBoxDialog::~MapPropertiesSkyBoxDialog(){

}

void MapPropertiesSkyBoxDialog::cancelButtonPressed(wxCommandEvent &event){
    //If the temporary sky box will not replace the new one then just delete it.
    delete tempSkyBox;
    Close();
}

void MapPropertiesSkyBoxDialog::okButtonPressed(wxCommandEvent &event){
    //If editing a skybox then update it's values, otherwise just add the new skybox to the manager.
    if(skyBoxNameTextCtrl->GetValue() == ""){
        wxMessageBox("Please Enter a name for the skybox.", "Skybox Creation Error", wxCENTRE | wxICON_ERROR);
        return;
    }
    tempSkyBox->setName(skyBoxNameTextCtrl->GetValue());

    //Check that each face has been assigned an image.
    bool ok = true;
    for(int i = 0; i < 6; i++){
        if(pathStrings[i]->GetLabel() == ""){
            ok = false;
        }
    }

    if(!ok){
        wxMessageBox("Please make sure that each face of the skybox has an image.", "Skybox Creation Error", wxCENTRE | wxICON_ERROR);
        return;
    }

    if(editedSkyBox){
        editedSkyBox->copyValuesFrom(tempSkyBox);

        delete tempSkyBox;
    }else{
        //Don't delete the temporary one if it's being added.
        parentDialog->getMainFrame()->getMain()->getSkyBoxManager()->addSkyBox(tempSkyBox);
    }

    parentDialog->updateSkyBoxes();

    Close();
}

void MapPropertiesSkyBoxDialog::imageButtonPressed(wxCommandEvent &event){
    ResourceSelectionPopup dialog(this, parentDialog->getMainFrame(), parentDialog->getMainFrame()->getResourceManager());

    int index = 0 ;
    for(int i = 0; i < 6; i++){
        if(buttonIDs[i] == event.GetId()){
            index = i;
        }
    }

    wxString value = dialog.getValue();
    if(value != ""){
        pathStrings[index]->SetLabel(value);
        tempSkyBox->setSkyBoxValue(index, value);
    }
    Layout();
}
