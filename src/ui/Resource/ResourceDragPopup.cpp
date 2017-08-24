#include "ResourceDragPopup.h"

#include "../Hierarchy/HierarchyTree.h"

ResourceDragPopup::ResourceDragPopup(HierarchyTree *tree) : wxPopupWindow(tree){
    this->tree = tree;

    SetSize(wxSize(100, 100));
    SetPosition(wxGetMousePosition());

    Show();
}

ResourceDragPopup::~ResourceDragPopup(){

}

void ResourceDragPopup::updatePopup(){
    SetPosition(wxGetMousePosition());
}
