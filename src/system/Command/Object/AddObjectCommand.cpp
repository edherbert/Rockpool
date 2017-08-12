#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem) : ObjectCommand(tree, parentItem){
    this->path = path;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    wxTreeItemId oldItem = childItem;
    if(parentItem == 0){
        childItem = tree->AddObject(object, path);
    }else{
        childItem = tree->AddObject(object, path, parentItem);
    }
    if(oldItem != 0){
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldItem, childItem);
    }
}

void AddObjectCommand::performAntiAction(){
    if(childItem != 0){
        tree->removeObject(childItem);
        //childItem = 0;
    }
}
