#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, int parentItem) : ObjectCommand(tree){
    this->path = path;
    this->parentItem = parentItem;

    wxTreeItemId targetItem;
    if(parentItem == -1){
        targetItem = tree->GetRootItem();
    }else{
        targetItem = tree->getItem(parentItem);
    }
    index = tree->GetChildrenCount(targetItem, false);

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    wxTreeItemId targetItem;
    if(parentItem == -1){
        targetItem = tree->GetRootItem();
    }else{
        targetItem = tree->getItem(parentItem);
    }

    //wxTreeItemId newItem = tree->AppendItem(targetItem, path);
    wxTreeItemId newItem = tree->InsertItem(targetItem, index, path);
    if(!ran){
        addedItem = tree->addItem(newItem);
    }else{
        tree->setItem(addedItem, newItem);
    }

    ran = true;
}

void AddObjectCommand::performAntiAction(){
    if(addedItem != -1){
        tree->Delete(tree->getItem(addedItem));
    }
}
