#include "Object.h"

Object::Object(Ogre::SceneManager *sceneManager, Ogre::SceneNode *parentNode, Ogre::String name){
    this->sceneManager = sceneManager;

    node = parentNode->createChildSceneNode(name);

    Ogre::Entity *ogreThing = sceneManager->createEntity("Sinbad.mesh");
    node->attachObject(ogreThing);
}

Object::Object(Ogre::SceneManager *sceneManager, Object *obj, Ogre::String name){
    this->sceneManager = sceneManager;

    node = obj->getSceneNode()->createChildSceneNode(name);

    Ogre::Entity *ogreThing = sceneManager->createEntity("Sinbad.mesh");
    node->attachObject(ogreThing);
}

Object::~Object(){

}

void Object::setPosition(Ogre::Vector3 pos){
    node->setPosition(pos);
}

void Object::attachChild(Object *child){

}

Ogre::SceneNode* Object::getSceneNode(){
    return node;
}
