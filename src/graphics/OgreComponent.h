#ifndef OGRECOMPONENT_H
#define OGRECOMPONENT_H

#include <OGRE/Ogre.h>
#include <OgrePlane.h>
#include <iostream>

class OgreComponent
{
    public:
        OgreComponent();
        virtual ~OgreComponent();

    protected:

    private:
        Ogre::Root *root;
};

#endif // OGRECOMPONENT_H
