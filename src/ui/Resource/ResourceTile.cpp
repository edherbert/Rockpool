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
    wxSystemSettings settings;

    //wxDC dc(this);
    wxClientDC dc(this);
    dc.SetFont(settings.GetFont(wxSYS_SYSTEM_FONT));

    wxSize fontSize = dc.GetTextExtent(l);

    wxString newString = "";
    int stringThreshold = 90;
    for(int i = 0; i < l.size(); i++){
        if(dc.GetTextExtent(l.substr(0, i + 1)).GetWidth() >= stringThreshold){
            newString.Append("\n");
            newString.Append(l[i]);
            stringThreshold += 90;
        }else{
            newString.Append(l[i]);
        }
    }

    label->SetLabel(newString);
    currentValue = l;

    int height = 50 + dc.GetTextExtent(newString).GetHeight();
    if(height < 100){
        setSize(100, 100);
    }else{
        setSize(100, height + 10);
    }

    Layout();
}

wxString ResourceTile::getLabel(){
    return label->GetLabel();
}

wxString ResourceTile::getValue(){
    return currentValue;
}

void ResourceTile::setId(int id){
    this->id = id;
    cover->setId(id);
}

int ResourceTile::getId(){
    return id;
}

void ResourceTile::setPosition(int x, int y){
    SetPosition(wxPoint(x, y));
    cover->SetPosition(wxPoint(x, y));
}

void ResourceTile::setSize(int width, int height){
    SetSize(width, height);
    cover->SetSize(width, height);
}

void ResourceTile::selectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_WINDOW));
}

void ResourceTile::deSelectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_MENU));
}
