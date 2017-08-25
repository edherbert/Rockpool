#include "ResourceDragPopup.h"

#include "ResourcePanel.h"
#include "ResourceTile.h"

ResourceDragPopup::ResourceDragPopup(ResourcePanel *panel) : wxPopupWindow(panel){
    this->panel = panel;

    SetPosition(wxGetMousePosition());

    tile = new ResourceTile(this, panel, panel->getDefaultBitmap());
    tile->setLabel(panel->getCurrentTile()->getValue());

    SetSize(panel->getCurrentTile()->getSize());

    Show();
}

ResourceDragPopup::~ResourceDragPopup(){

}

void ResourceDragPopup::update(){
    SetPosition(wxGetMousePosition());
}
