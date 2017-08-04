#ifndef OBJECT_H
#define OBJECT_H

#include <Ogre.h>

class Object
{
    public:
        Object(Ogre::SceneManager *sceneManager, Ogre::SceneNode *parentNode, Ogre::String name = "");
        Object(Ogre::SceneManager *sceneManager, Object *obj, Ogre::String name = "");

        virtual ~Object();

        void setPosition(Ogre::Vector3 pos);
        void attachChild(Object *child);

        Ogre::SceneNode* getSceneNode();

    protected:

    private:
        Ogre::SceneManager *sceneManager;
        Ogre::SceneNode *node;
};

#endif // OBJECT_H
