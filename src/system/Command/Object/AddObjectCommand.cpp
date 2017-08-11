#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem){
    this->tree = tree;
    this->parentItem = parentItem;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    if(parentItem == 0){
        tree->AddObject(object, "Cube");
    }else{
        tree->AddObject(object, "Cube", parentItem);
    }
}

void AddObjectCommand::performAntiAction(){

}
