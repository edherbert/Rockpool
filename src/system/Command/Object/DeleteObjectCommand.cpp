#include "DeleteObjectCommand.h"

DeleteObjectCommand::DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){
    this->items = items;
}

DeleteObjectCommand::~DeleteObjectCommand(){

}

void DeleteObjectCommand::performAction(){
    for(int i = 0; i < items.size(); i++){
        tree->Delete(items[i]);
    }
}

void DeleteObjectCommand::performAntiAction(){

}
