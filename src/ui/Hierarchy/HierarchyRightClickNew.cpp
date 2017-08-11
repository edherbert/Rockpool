#include "HierarchyRightClickNew.h"

HierarchyRightClickNew::HierarchyRightClickNew(HierarchyTree *hierarchyTree, wxArrayTreeItemIds selection){
    this->hierarchyTree = hierarchyTree;
    this->selection = selection;

    Append(HIERARCHY_MENU_ADD_EMPTY, wxT("Empty Object"));
    AppendSeparator();
    Append(HIERARCHY_MENU_ADD_CUBE, wxT("Cube"));
    Append(HIERARCHY_MENU_ADD_SPHERE, wxT("Sphere"));
    Append(HIERARCHY_MENU_ADD_CONE, wxT("Cone"));
    Append(HIERARCHY_MENU_ADD_PLANE, wxT("Plane"));

    Connect(HIERARCHY_MENU_ADD_EMPTY, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addEmptyClick));
    Connect(HIERARCHY_MENU_ADD_CUBE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addCubeClick));
}

HierarchyRightClickNew::~HierarchyRightClickNew(){

}

void HierarchyRightClickNew::addEmptyClick(wxCommandEvent &event){
    AddObjectCommand *command;

    if(selection.size() <= 0){
        command = new AddObjectCommand("Empty", hierarchyTree);
    }else{
        command = new AddObjectCommand("Empty", hierarchyTree, selection[0]);
    }

    command->performAction();
    hierarchyTree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
}

void HierarchyRightClickNew::addCubeClick(wxCommandEvent &event){
}
