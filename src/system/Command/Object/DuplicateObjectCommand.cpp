#include "DuplicateObjectCommand.h"

DuplicateObjectCommand::DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){

}

DuplicateObjectCommand::~DuplicateObjectCommand(){

}

void DuplicateObjectCommand::performAction(){
    std::cout << "Duplicate" << std::endl;
}

void DuplicateObjectCommand::performAntiAction(){

}
