#include "BottomPanel.h"

BottomPanel::BottomPanel(wxPanel *parentPanel){
    this->parentPanel = parentPanel;

    wxBoxSizer *horizontalBox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *info = new wxStaticText(parentPanel, wxID_ANY, wxT("Hello"));

    wxBitmapToggleButton *playerCameraButton = new wxBitmapToggleButton(parentPanel, wxID_ANY, wxBitmap("../media/img/icon.png"));


    horizontalBox->Add(info, 1, wxALIGN_LEFT | wxBOTTOM | wxTOP, 15);
    horizontalBox->Add(playerCameraButton, 0, wxALIGN_RIGHT | wxALL, 10);

    parentPanel->SetSizer(horizontalBox);
}

BottomPanel::~BottomPanel(){

}
