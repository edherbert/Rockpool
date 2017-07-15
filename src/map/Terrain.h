#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <Ogre.h>

#include <cmath>
#include <vector>

class Terrain
{
    public:
        Terrain(Ogre::SceneManager *sceneManager, std::string path, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);
        virtual ~Terrain();

        Ogre::TerrainGroup::RayResult rayIntersect(Ogre::Ray ray);

        void setHeightFromRays(Ogre::TerrainGroup::RayResult centreRay,
        Ogre::TerrainGroup::RayResult leftTopResult,
        Ogre::TerrainGroup::RayResult rightTopResult,
        Ogre::TerrainGroup::RayResult leftBottomResult,
        Ogre::TerrainGroup::RayResult rightBottomResult, int brushSize, int brushFlow);

        void setBlendFromRays(Ogre::TerrainGroup::RayResult centreRay, int brushSize, int brushFlow, int layerIndex);

        void saveTerrains();


    protected:

    private:
        Ogre::TerrainGlobalOptions* terrainGlobals;
        Ogre::TerrainGroup *terrainGroup;
        Ogre::SceneManager *sceneManager;

        int vertexCount;
        int terrainSize;
        int terrainHeight;
        std::string path;

        bool vectorContains(std::vector<Ogre::Terrain*> *terrains, Ogre::Terrain* terrain);

        void destroyScene();
        void configureTerrainDefaults();
        void checkAndDefineTerrain(int x, int y);
};

#endif // TERRAIN_H
