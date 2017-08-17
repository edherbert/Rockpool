#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, int parentItem) : ObjectCommand(tree){
    this->path = path;
    this->parentItem = parentItem;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    /*wxTreeItemId oldItem = addedItem;
    if(parentItem == 0){
        addedItem = tree->AddObject(object, path);
    }else{
        addedItem = tree->AddObject(object, path, parentItem);
    }
    //The older item will be 0 when first added, so there's no need to check it's value in the command stack.
    if(oldItem != 0){
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldItem, addedItem);
    }*/
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
//        tree->removeObject(addedItem);
        tree->Delete(tree->getItem(addedItem));
    }
}

void AddObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
    /*if(parentItem == oldId){
        parentItem = newId;
    }
    if(addedItem == oldId){
        addedItem = newId;
    }*/
}
