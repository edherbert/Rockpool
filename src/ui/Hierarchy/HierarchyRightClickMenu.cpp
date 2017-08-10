#include "HierarchyRightClickMenu.h"

HierarchyRightClickMenu::HierarchyRightClickMenu(wxWindow *parent, wxPoint location, wxArrayTreeItemIds selection) : wxMenu(){
    this->parent = parent;
    this->location = location;

    HierarchyRightClickNew *addObjectMenu = new HierarchyRightClickNew();

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
}

HierarchyRightClickMenu::~HierarchyRightClickMenu(){

}

void HierarchyRightClickMenu::popup(){
    parent->PopupMenu(this, location);
}
