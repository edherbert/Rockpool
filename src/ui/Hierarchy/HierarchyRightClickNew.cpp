#include "HierarchyRightClickNew.h"

#include "../../map/Main.h"
#include "../../system/Command/CommandManager.h"
#include "../GLCanvas.h"

HierarchyRightClickNew::HierarchyRightClickNew(HierarchyTree *hierarchyTree, wxArrayTreeItemIds selection){
    this->hierarchyTree = hierarchyTree;
    this->selection = selection;

    Append(HIERARCHY_MENU_ADD_EMPTY, wxT("Empty Object"));
    AppendSeparator();
    Append(HIERARCHY_MENU_ADD_CUBE, wxT("Cube"));
    Append(HIERARCHY_MENU_ADD_SPHERE, wxT("Sphere"));
    Append(HIERARCHY_MENU_ADD_CONE, wxT("Cone"));
    Append(HIERARCHY_MENU_ADD_PLANE, wxT("Plane"));

    Connect(HIERARCHY_MENU_ADD_EMPTY, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addItem));
    Connect(HIERARCHY_MENU_ADD_CUBE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addItem));
    Connect(HIERARCHY_MENU_ADD_SPHERE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addItem));
    Connect(HIERARCHY_MENU_ADD_CONE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addItem));
    Connect(HIERARCHY_MENU_ADD_PLANE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickNew::addItem));
}

HierarchyRightClickNew::~HierarchyRightClickNew(){

}

void HierarchyRightClickNew::addItem(wxCommandEvent &event){
    AddObjectCommand *command;

    PrimativeIds type;
    if(event.GetId() == HIERARCHY_MENU_ADD_EMPTY) type = PrimativeEmpty;
    else if(event.GetId() == HIERARCHY_MENU_ADD_CUBE) type = PrimativeCube;
    else if(event.GetId() == HIERARCHY_MENU_ADD_SPHERE) type = PrimativeSphere;
    else if(event.GetId() == HIERARCHY_MENU_ADD_CONE) type = PrimativeCone;
    else if(event.GetId() == HIERARCHY_MENU_ADD_PLANE) type = PrimativePlane;

    if(selection.size() <= 0){
        //Append to the root item
        command = new AddObjectCommand(type, hierarchyTree);
    }else{
        //Append below the specified item
        command = new AddObjectCommand(type, hierarchyTree, hierarchyTree->getId(selection[0]));
    }

    command->performAction();
    hierarchyTree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
}
