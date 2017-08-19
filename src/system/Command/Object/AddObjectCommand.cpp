#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, int parentItem) : ObjectCommand(tree){
    this->path = path;
    this->parentItem = parentItem;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    if(!ran){
        if(parentItem == -1){
            wxTreeItemId newItem = tree->AppendItem(tree->GetRootItem(), path);
            addedItem = tree->addItem(newItem);
        }else{
            wxTreeItemId newItem = tree->AppendItem(tree->getItem(parentItem), path);
            addedItem = tree->addItem(newItem);
        }
    }else{
        if(parentItem == -1){
            wxTreeItemId newItem = tree->AppendItem(tree->GetRootItem(), path);
            tree->setItem(addedItem, newItem);
        }else{
            wxTreeItemId newItem = tree->AppendItem(tree->getItem(parentItem), path);
            tree->setItem(addedItem, newItem);
        }
    }

    ran = true;
}

void AddObjectCommand::performAntiAction(){
    if(addedItem != -1){
        tree->Delete(tree->getItem(addedItem));
    }
}
