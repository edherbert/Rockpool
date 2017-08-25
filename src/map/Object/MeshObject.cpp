#include "MeshObject.h"

MeshObject::MeshObject(Ogre::SceneManager *sceneManager, const wxString &name, const wxString &path) : Object(sceneManager){
    this->path = path;
    this->name = name;
    this->type = ObjectTypeMesh;

    objectEntity = sceneManager->createEntity((Ogre::String)path);
    node->attachObject(objectEntity);
}

MeshObject::MeshObject(MeshObject *meshObject) : Object(meshObject){
    this->path = meshObject->getPath();
    this->name = meshObject->getName();
    this->type = ObjectTypeMesh;

    objectEntity = sceneManager->createEntity((Ogre::String)path);
    node->attachObject(objectEntity);
}

MeshObject::~MeshObject(){

}

wxString MeshObject::getName(){
    return name;
}

wxString MeshObject::getPath(){
    return path;
}
