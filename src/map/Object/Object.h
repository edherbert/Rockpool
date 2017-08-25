#ifndef OBJECT_H
#define OBJECT_H

#include <Ogre.h>
#include <iostream>

enum ObjectType{
    ObjectTypeObject,
    ObjectTypeMesh
};

class Object
{
    public:
        Object(Ogre::SceneManager *sceneManager);
        Object(Object *object);

        virtual ~Object();

        void setPosition(const Ogre::Vector3 &pos);
        void setPosition(int x, int y, int z);

        void setScale(int x, int y, int z);
        void setScale(const Ogre::Vector3 &scale);

        void setParent(Object *parent);
        void addChild(Object *child);

        void removeChild(Object *child);
        void removeAllChildren();
        void removeFromParent();

        ObjectType getType();

        Ogre::SceneNode* getSceneNode();

        const Ogre::Vector3& getPosition();
        const Ogre::Vector3& getScale();

        Ogre::SceneManager* getSceneManager();

    protected:
        Ogre::SceneManager *sceneManager;
        Ogre::SceneNode *node;

        ObjectType type = ObjectTypeObject;

        Object *parent;
        std::vector<Object*>children;
    private:
};

#endif // OBJECT_H
