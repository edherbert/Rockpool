#include "ResourceTile.h"

ResourceTile::ResourceTile(ResourcePanel *parent, wxBitmap *defaultBitmap) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(100, 100)){
    this->parent = parent;
    this->defaultBitmap = defaultBitmap;

    //SetBackgroundColour(wxColour("#FF0000"));

    //wxStaticBitmap *icon = new wxStaticBitmap(this, wxID_ANY, defaultIcon, wxPoint(25, 0), wxSize(50, 50));
    //icon->SetScaleMode()
//    icon->SetScaleMode(1);

    wxStaticBitmap *icon = new wxStaticBitmap(this, wxID_ANY, *defaultBitmap, wxPoint(25, 0), wxSize(50, 50));

    //wxPanel *tempPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 50));
    //wxPanel *tempPanel = new wxPanel(this, wxID_ANY);

    //tempPanel->SetBackgroundColour(wxColor("#00FF00"));

    label = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *horizontal = new wxBoxSizer(wxHORIZONTAL);

    horizontal->Add(new wxPanel(this), 1, wxEXPAND);
    //horizontal->Add(tempPanel, 0);
    horizontal->Add(icon, 0);
    horizontal->Add(new wxPanel(this), 1, wxEXPAND);

    verticalSizer->Add(wxID_ANY, 2);
    verticalSizer->Add(horizontal, 0, wxEXPAND);
    verticalSizer->Add(label, 1, wxEXPAND);

    SetSizer(verticalSizer);

    label->Wrap(100);

    //cover = new wxPanel(parent,wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    cover = new ResourceTileCover(parent, this);
}

ResourceTile::~ResourceTile(){

}

void ResourceTile::setLabel(wxString l){
    label->SetLabel(l);
}

wxString ResourceTile::getLabel(){
    return label->GetLabel();
}

void ResourceTile::setPosition(int x, int y){
    SetPosition(wxPoint(x, y));
    cover->SetPosition(wxPoint(x, y));
}

void ResourceTile::selectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_WINDOW));
}

void ResourceTile::deSelectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_MENU));
}
