#include "HierarchyRightClickMenu.h"

HierarchyRightClickMenu::HierarchyRightClickMenu(wxWindow *parent, wxPoint location) : wxMenu(){
    this->parent = parent;
    this->location = location;

    wxMenu *addObject = new wxMenu;
    addObject->Append(wxID_ANY, wxT("Cube"));
    addObject->Append(wxID_ANY, wxT("Sphere"));
    addObject->Append(wxID_ANY, wxT("Cone"));
    addObject->Append(wxID_ANY, wxT("Plane"));

    AppendSubMenu(addObject, wxT("Add Object"));
    AppendSeparator();
    Append(wxID_ANY, wxT("Copy"));
    Append(wxID_ANY, wxT("Paste"));
    Append(wxID_ANY, wxT("Delete"));
    Append(wxID_ANY, wxT("Duplicate"));
    AppendSeparator();
    Append(wxID_ANY, wxT("Rename"));
}

HierarchyRightClickMenu::~HierarchyRightClickMenu(){

}

void HierarchyRightClickMenu::popup(){
    parent->PopupMenu(this, location);
}
