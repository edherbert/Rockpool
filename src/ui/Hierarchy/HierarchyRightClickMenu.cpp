#include "HierarchyRightClickMenu.h"

#include "../../map/Main.h"
#include "../../system/Command/CommandManager.h"

HierarchyRightClickMenu::HierarchyRightClickMenu(HierarchyTree *hierarchyTree, wxPoint location, const wxArrayTreeItemIds &selection) : wxMenu(){
    this->hierarchyTree = hierarchyTree;
    this->location = location;
    this->selection = selection;

    HierarchyRightClickNew *addObjectMenu = new HierarchyRightClickNew(hierarchyTree, selection);

    wxMenuItem *addObject = AppendSubMenu(addObjectMenu, wxT("Add Object"));
    AppendSeparator();
    wxMenuItem *cutItem = Append(HIERARCHY_MENU_CUT, wxT("Cut"));
    wxMenuItem *copyItem = Append(HIERARCHY_MENU_COPY, wxT("Copy"));
    wxMenuItem *pasteItem = Append(HIERARCHY_MENU_PASTE, wxT("Paste"));
    AppendSeparator();
    wxMenuItem *deleteItem = Append(HIERARCHY_MENU_DELETE, wxT("Delete"));
    wxMenuItem *duplicateItem = Append(HIERARCHY_MENU_DUPLICATE, wxT("Duplicate"));
    AppendSeparator();
    wxMenuItem *renameItem = Append(HIERARCHY_MENU_RENAME, wxT("Rename"));

    if(selection.size() > 1){
        addObject->Enable(false);
        renameItem->Enable(false);
    }
    if(selection.size() <= 0){
        cutItem->Enable(false);
        copyItem->Enable(false);
        deleteItem->Enable(false);
        renameItem->Enable(false);
        duplicateItem->Enable(false);
    }

    Connect(HIERARCHY_MENU_CUT, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickMenu::itemClick));
    Connect(HIERARCHY_MENU_COPY, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickMenu::itemClick));
    Connect(HIERARCHY_MENU_PASTE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickMenu::itemClick));
    Connect(HIERARCHY_MENU_DELETE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickMenu::itemClick));
    Connect(HIERARCHY_MENU_DUPLICATE, wxEVT_MENU, wxCommandEventHandler(HierarchyRightClickMenu::itemClick));
}

HierarchyRightClickMenu::~HierarchyRightClickMenu(){

}

void HierarchyRightClickMenu::popup(){
    hierarchyTree->PopupMenu(this, location);
}

void HierarchyRightClickMenu::itemClick(wxCommandEvent &event){
    if(event.GetId() == HIERARCHY_MENU_CUT){
        hierarchyTree->getObjectHierarchy()->cutItems();
    }else if(event.GetId() == HIERARCHY_MENU_COPY){
        hierarchyTree->getObjectHierarchy()->copyItems();
    }else if(event.GetId() == HIERARCHY_MENU_PASTE){
        hierarchyTree->getObjectHierarchy()->pasteItems();
    }else if(event.GetId() == HIERARCHY_MENU_DELETE){
        hierarchyTree->getObjectHierarchy()->deleteItems();
    }else if(event.GetId() == HIERARCHY_MENU_DUPLICATE){
        DuplicateObjectCommand *command = new DuplicateObjectCommand(hierarchyTree, selection);

        command->performAction();
        hierarchyTree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
    }
}

