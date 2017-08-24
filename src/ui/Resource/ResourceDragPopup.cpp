#include "ResourceDragPopup.h"

#include "ResourcePanel.h"

ResourceDragPopup::ResourceDragPopup(ResourcePanel *panel) : wxPopupWindow(panel){
    this->panel = panel;

    SetSize(wxSize(100, 100));
    SetPosition(wxGetMousePosition());

    Show();
}

ResourceDragPopup::~ResourceDragPopup(){

}

void ResourceDragPopup::update(){
    SetPosition(wxGetMousePosition());
}
