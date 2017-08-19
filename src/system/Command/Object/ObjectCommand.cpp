#include "ObjectCommand.h"

ObjectCommand::ObjectCommand(HierarchyTree *tree){
    this->tree = tree;

    this->type = objectCommand;
}

ObjectCommand::~ObjectCommand(){

}
