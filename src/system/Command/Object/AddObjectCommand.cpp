#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem){
    this->path = path;
    this->tree = tree;
    this->parentItem = parentItem;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    if(parentItem == 0){
        childItem = tree->AddObject(object, path);
    }else{
        childItem = tree->AddObject(object, path, parentItem);
    }
}

void AddObjectCommand::performAntiAction(){
    if(childItem != 0){
        tree->removeObject(childItem);
        childItem = 0;
    }
}
