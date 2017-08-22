#ifndef OBJECT_H
#define OBJECT_H

#include <Ogre.h>
#include <iostream>

class Object
{
    public:
        Object(Ogre::SceneManager *sceneManager);

        virtual ~Object();

        void setPosition(Ogre::Vector3 pos);
        void setPosition(int x, int y, int z);

        void setScale(int x, int y, int z);
        void setScale(Ogre::Vector3 scale);

        void setParent(Object *parent);
        void addChild(Object *child);

        void removeChild(Object *child);
        void removeAllChildren();
        void removeFromParent();

        Ogre::SceneNode* getSceneNode();
        const Ogre::Vector3& getPosition();

    protected:
        Ogre::SceneManager *sceneManager;
        Ogre::SceneNode *node;

        Object *parent;
        std::vector<Object*>children;
    private:
};

#endif // OBJECT_H
