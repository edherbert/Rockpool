#include "ObjectCommand.h"

ObjectCommand::ObjectCommand(HierarchyTree *tree, wxTreeItemId parentItem){
    this->tree = tree;
    this->parentItem = parentItem;

    this->type = objectCommand;
}

ObjectCommand::~ObjectCommand(){

}

//This function replaces the id of the previous item with a new one.
//Basically, I was having a problem with the hierarchy when undoing and redoing actions.
//By removing something from the hierarchy, it needs to be deleted
//The problem came with the commands, as I was storing the id of the parent in each command.
//If the action was undone, the item would be deleted form the hierarchy.
//By re-doing the action, a new item would be created that looked identical, but the ids were different.
//This would lead to a mismatch of which item should go where.

//This function works by running through the command stack and checking for the parent id.
//When an item is added, it checks through the stack to see if any items reference it's previous value
//If they do, it's replaced with the new id
//This would mean that every command knows where to re-insert it's children items, regardless of whether the id changed.
void ObjectCommand::checkParent(wxTreeItemId oldId, wxTreeItemId newId){
    if(parentItem.GetID() == oldId.GetID()){
    std::cout << "replacing item with id " << oldId.GetID() << " with " << newId.GetID() << std::endl;
        parentItem = newId;
    }
}
