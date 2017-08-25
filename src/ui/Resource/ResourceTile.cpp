#include "ResourceTile.h"

#include "ResourcePanel.h"
#include "ResourceTileCover.h"

ResourceTile::ResourceTile(wxWindow *parent, ResourcePanel *resPanel, wxBitmap *defaultBitmap) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(100, 100)){
    this->resPanel = resPanel;
    this->defaultBitmap = defaultBitmap;
    this->parent = parent;

    wxStaticBitmap *icon = new wxStaticBitmap(this, wxID_ANY, *defaultBitmap, wxPoint(25, 0), wxSize(50, 50));

    label = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);

    wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *horizontal = new wxBoxSizer(wxHORIZONTAL);

    horizontal->Add(new wxPanel(this), 1, wxEXPAND);

    horizontal->Add(icon, 0);
    horizontal->Add(new wxPanel(this), 1, wxEXPAND);

    verticalSizer->Add(wxID_ANY, 2);
    verticalSizer->Add(horizontal, 0, wxEXPAND);
    verticalSizer->Add(label, 1, wxEXPAND);

    SetSizer(verticalSizer);

    label->Wrap(100);

    cover = new ResourceTileCover(resPanel, this);
}

ResourceTile::~ResourceTile(){

}

void ResourceTile::setLabel(const wxString &l){
    wxSystemSettings settings;

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

wxSize ResourceTile::getSize(){
    return GetSize();
}
