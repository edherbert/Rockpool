#include "ResourceTile.h"

ResourceTile::ResourceTile(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(100, 100), wxBORDER_SIMPLE){
    this->parent = parent;

    SetBackgroundColour(wxColour("#FF0000"));

    wxBitmap defaultIcon("../media/temp/grass.jpg");

    //wxStaticBitmap *icon = new wxStaticBitmap(this, wxID_ANY, defaultIcon, wxPoint(25, 0), wxSize(50, 50));
    //icon->SetScaleMode()
//    icon->SetScaleMode(1);

    wxPanel *tempPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 50));
    //wxPanel *tempPanel = new wxPanel(this, wxID_ANY);

    tempPanel->SetBackgroundColour(wxColor("#00FF00"));

    label = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *horizontal = new wxBoxSizer(wxHORIZONTAL);

    horizontal->Add(new wxPanel(this), 1, wxEXPAND);
    horizontal->Add(tempPanel, 0);
    horizontal->Add(new wxPanel(this), 1, wxEXPAND);

    verticalSizer->Add(horizontal, 0, wxEXPAND);
    verticalSizer->Add(label, 1, wxEXPAND);

    SetSizer(verticalSizer);

    label->Wrap(100);
}

ResourceTile::~ResourceTile(){

}

void ResourceTile::setLabel(wxString l){
    label->SetLabel(l);
}
