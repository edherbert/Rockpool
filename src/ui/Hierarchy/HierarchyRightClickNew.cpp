#include "HierarchyRightClickNew.h"

HierarchyRightClickNew::HierarchyRightClickNew(HierarchyTree *hierarchyTree){
    this->hierarchyTree = hierarchyTree;

    Append(HIERARCHY_MENU_ADD_EMPTY, wxT("Empty Object"));
    AppendSeparator();
    Append(HIERARCHY_MENU_ADD_CUBE, wxT("Cube"));
    Append(HIERARCHY_MENU_ADD_SPHERE, wxT("Sphere"));
    Append(HIERARCHY_MENU_ADD_CONE, wxT("Cone"));
    Append(HIERARCHY_MENU_ADD_PLANE, wxT("Plane"));

    Connect(HIERARCHY_MENU_ADD_CUBE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addCubeClick));
}

HierarchyRightClickNew::~HierarchyRightClickNew(){

}

void HierarchyRightClickNew::addCubeClick(wxCommandEvent &event){
    AddObjectCommand *command = new AddObjectCommand("cube", hierarchyTree);
}
