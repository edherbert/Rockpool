#include "HierarchyRightClickNew.h"

#include "../../map/Main.h"
#include "../../system/Command/CommandManager.h"

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

    wxString name;
    if(event.GetId() == HIERARCHY_MENU_ADD_EMPTY) name = "Empty";
    else if(event.GetId() == HIERARCHY_MENU_ADD_CUBE) name = "Cube";
    else if(event.GetId() == HIERARCHY_MENU_ADD_SPHERE) name = "Sphere";
    else if(event.GetId() == HIERARCHY_MENU_ADD_CONE) name = "Cone";
    else if(event.GetId() == HIERARCHY_MENU_ADD_PLANE) name = "Plane";

    if(selection.size() <= 0){
        command = new AddObjectCommand(name, hierarchyTree);
    }else{
        command = new AddObjectCommand(name, hierarchyTree, hierarchyTree->getId(selection[0]));
    }

    command->performAction();
    hierarchyTree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
}
