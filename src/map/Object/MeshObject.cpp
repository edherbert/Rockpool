#include "MeshObject.h"

MeshObject::MeshObject(Ogre::SceneManager *sceneManager, const wxString &name, const wxString &path) : Object(sceneManager){
    this->path = path;
    this->name = name;

    objectEntity = sceneManager->createEntity((Ogre::String)path);
    node->attachObject(objectEntity);
}

MeshObject::~MeshObject(){

}
