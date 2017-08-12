#include "Object.h"

Object::Object(Ogre::SceneManager *sceneManager){
    this->sceneManager = sceneManager;

    /*node = parent->getSceneNode()->createChildSceneNode(name);

    Ogre::Entity *ogreThing = sceneManager->createEntity("Sinbad.mesh");
    node->attachObject(ogreThing);*/
    node = sceneManager->createSceneNode();

    //Ogre::Entity *ogreThing = sceneManager->createEntity("Sinbad.mesh");
    //node->attachObject(ogreThing);
}

Object::~Object(){

}

void Object::setPosition(Ogre::Vector3 pos){
    node->setPosition(pos);
}

void Object::setPosition(int x, int y, int z){
    node->setPosition(x, y, z);
}

void Object::setScale(int x, int y, int z){
    node->setScale(x, y, z);
}

void Object::setScale(Ogre::Vector3 scale){
    node->setScale(scale);
}

void Object::addChild(Object *child){
    child->setParent(this);
    children.push_back(child);
}

void Object::removeChild(Object *child){
    for(int i = children.size() - 1; i >= 0; i--){
        if(children.at(i) == child){
            children.erase(children.begin() + i);
        }
    }
    node->removeChild(child->getSceneNode());
}

void Object::removeAllChildren(){
    node->removeAllChildren();
    children.clear();
}

void Object::removeFromParent(){
    parent->removeChild(this);
    parent = 0;
}

void Object::setParent(Object *parent){
    this->parent = parent;
    parent->getSceneNode()->addChild(node);
}

Ogre::SceneNode* Object::getSceneNode(){
    return node;
}
