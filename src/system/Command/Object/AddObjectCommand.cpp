#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem) : ObjectCommand(tree, parentItem){
    this->path = path;

    object = new Object(tree->getMap()->getSceneManager());
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::performAction(){
    wxTreeItemId oldItem = addedItem;
    if(parentItem == 0){
        addedItem = tree->AddObject(object, path);
    }else{
        addedItem = tree->AddObject(object, path, parentItem);
    }
    //The older item will be 0 when first added, so there's no need to check it's value in the command stack.
    if(oldItem != 0){
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldItem, addedItem);
    }
}

void AddObjectCommand::performAntiAction(){
    if(addedItem != 0){
        tree->removeObject(addedItem);
    }
}
