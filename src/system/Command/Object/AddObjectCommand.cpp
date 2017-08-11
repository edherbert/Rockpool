#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, HierarchyTree *tree){
    this->tree = tree;

    object = new Object(tree->getMap()->getSceneManager());

    tree->AddObject(object, "Cube");
}

AddObjectCommand::~AddObjectCommand(){

}
