#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(wxString path, Ogre::SceneManager *sceneManager, HierarchyTree *tree){
    this->sceneManager = sceneManager;
    this->tree = tree;

    object = new Object(sceneManager);

    tree->AddObject(object, "Cube");
}

AddObjectCommand::~AddObjectCommand(){

}
