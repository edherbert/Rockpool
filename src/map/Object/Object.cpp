#include "Object.h"

Object::Object(Ogre::SceneManager *sceneManager){
    this->sceneManager = sceneManager;

    node = sceneManager->createSceneNode();
}

Object::Object(Object *object){
    this->sceneManager = object->getSceneManager();
    node = sceneManager->createSceneNode();

    node->setPosition(object->getPosition());
    node->setScale(object->getScale());
}

Object::~Object(){

}

void Object::setPosition(const Ogre::Vector3 &pos){
    node->setPosition(pos);
}

void Object::setPosition(int x, int y, int z){
    node->setPosition(x, y, z);
}

void Object::setAxisPosition(ObjectAxis axis, Ogre::Real position){
    Ogre::Vector3 newPosition = node->getPosition();
    newPosition[axis] = position;

    node->setPosition(newPosition);
}

void Object::setScale(int x, int y, int z){
    node->setScale(x, y, z);
}

const Ogre::Vector3& Object::getPosition(){
    return node->getPosition();
}

void Object::setScale(const Ogre::Vector3 &scale){
    node->setScale(scale);
}

void Object::setAxisScale(ObjectAxis axis, Ogre::Real scale){
    Ogre::Vector3 newScale = node->getScale();
    newScale[axis] = scale;

    node->setScale(newScale);
}

const Ogre::Vector3& Object::getScale(){
    return node->getScale();
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

Ogre::SceneManager* Object::getSceneManager(){
    return sceneManager;
}

ObjectType Object::getType(){
    return type;
}
