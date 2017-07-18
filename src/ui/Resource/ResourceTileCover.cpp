#include "ResourceTileCover.h"

ResourceTileCover::ResourceTileCover(ResourcePanel *resPanel, ResourceTile *parent) : wxPanel(resPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 100)){
    this->resPanel = resPanel;
    this->parent = parent;

    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ResourceTileCover::coverClicked));
}

ResourceTileCover::~ResourceTileCover(){

}

void ResourceTileCover::coverClicked(wxMouseEvent &event){
    int x, y;
    GetPosition(&x, &y);
    resPanel->selectTile(x / 100, y / 100);
}
