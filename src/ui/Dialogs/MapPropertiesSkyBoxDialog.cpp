#include "MapPropertiesSkyBoxDialog.h"

#include <wx/wx.h>

#include "../wxIDs.h"

MapPropertiesSkyBoxDialog::MapPropertiesSkyBoxDialog(wxWindow *parent) : wxDialog(parent, wxID_ANY, wxT("SkyBox Properties"), wxDefaultPosition, wxSize(500, 500)){
    wxBoxSizer *skyBoxDialogMainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(skyBoxDialogMainSizer);

    wxBoxSizer *skyBoxNameHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *skyBoxNameStaticText = new wxStaticText(this, wxID_ANY, wxT("SkyBox Name"));
    wxTextCtrl *skyBoxNameTextCtrl = new wxTextCtrl(this, wxID_ANY);

    skyBoxNameHorizontalSizer->Add(skyBoxNameStaticText, 0, wxALL, 10);
    skyBoxNameHorizontalSizer->Add(skyBoxNameTextCtrl, 1, wxRIGHT | wxTOP | wxBOTTOM, 10);

    wxGridSizer *skyBoxGridSizer = new wxGridSizer(2, 3, 5, 5);

    wxString imageNames[6] = {"Front", "Back", "Left", "Right", "Top", "Bottom"};

    wxColour blue("#0000FF");
    wxBitmap iconImage(wxT("../media/img/icon.png"));
    for(int i = 0; i < 6; i++){
        wxPanel *content = new wxPanel(this);
        //content->SetBackgroundColour(blue);

        wxBoxSizer *contentVertical = new wxBoxSizer(wxVERTICAL);

        wxStaticBitmap *icon = new wxStaticBitmap(content, wxID_ANY, iconImage);
        wxStaticText *label = new wxStaticText(content, wxID_ANY, imageNames[i]);

        contentVertical->Add(icon, 1, wxEXPAND);
        contentVertical->Add(label, 0, wxALIGN_CENTRE_HORIZONTAL);

        content->SetSizer(contentVertical);
        skyBoxGridSizer->Add(content, 1, wxEXPAND);
    }

    wxBoxSizer *skyBoxHorizontalButtons = new wxBoxSizer(wxHORIZONTAL);
    wxButton *cancelButton = new wxButton(this, DIALOG_SKYBOX_CANCEL, wxT("Cancel"));
    wxButton *OkButton = new wxButton(this, wxID_ANY, wxT("OK"));

    skyBoxHorizontalButtons->Add(cancelButton, 0, wxALL, 10);
    skyBoxHorizontalButtons->Add(new wxPanel(this), 1, wxEXPAND);
    skyBoxHorizontalButtons->Add(OkButton, 0, wxALL, 10);

    skyBoxDialogMainSizer->Add(skyBoxNameHorizontalSizer, 0, wxEXPAND);
    skyBoxDialogMainSizer->Add(skyBoxGridSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
    skyBoxDialogMainSizer->Add(skyBoxHorizontalButtons, 0, wxEXPAND);

    Connect(DIALOG_SKYBOX_CANCEL, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesSkyBoxDialog::cancelButtonPressed));

    ShowModal();
}

MapPropertiesSkyBoxDialog::~MapPropertiesSkyBoxDialog(){

}

void MapPropertiesSkyBoxDialog::cancelButtonPressed(wxCommandEvent &event){
std::cout << "hello" << std::endl;
    Close();
}
