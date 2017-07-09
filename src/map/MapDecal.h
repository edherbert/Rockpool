#ifndef MAPDECAL_H
#define MAPDECAL_H

#include "Terrain.h"
#include <OGRE/Ogre.h>

class MapDecal
{
    public:
        MapDecal(Ogre::SceneManager *sceneManager, Terrain *terrain);
        virtual ~MapDecal();

        void setPosition(int x, int y);
        void setRadius(int radius);

        void calculateGeometry();

    protected:

    private:
        Ogre::SceneManager *sceneManager;
        Terrain *terrain;

        int x, y, radius;

        Ogre::ManualObject *object;
};

#endif // MAPDECAL_H
