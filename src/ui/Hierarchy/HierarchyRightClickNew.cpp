#include "HierarchyRightClickNew.h"

HierarchyRightClickNew::HierarchyRightClickNew(){
    Append(HIERARCHY_MENU_ADD_CUBE, wxT("Cube"));
    Append(HIERARCHY_MENU_ADD_SPHERE, wxT("Sphere"));
    Append(HIERARCHY_MENU_ADD_CONE, wxT("Cone"));
    Append(HIERARCHY_MENU_ADD_PLANE, wxT("Plane"));

    Connect(HIERARCHY_MENU_ADD_CUBE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addCubeClick));
}

HierarchyRightClickNew::~HierarchyRightClickNew(){

}

void HierarchyRightClickNew::addCubeClick(wxCommandEvent &event){
    std::cout << "cube" << std::endl;
}
