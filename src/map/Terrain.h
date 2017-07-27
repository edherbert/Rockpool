#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <Ogre.h>

#include <cmath>
#include <vector>

struct terrainRays{
    Ogre::TerrainGroup::RayResult centreRay;
    Ogre::TerrainGroup::RayResult leftTop;
    Ogre::TerrainGroup::RayResult rightTop;
    Ogre::TerrainGroup::RayResult leftBottom;
    Ogre::TerrainGroup::RayResult rightBottom;
};

struct terrainTextureCommandInformation{
    int x;
    int y;
    float layer1;
    float layer2;
    float layer3;
};

class Terrain
{
    public:
        Terrain(Ogre::SceneManager *sceneManager, std::string path, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);
        virtual ~Terrain();

        Ogre::TerrainGroup::RayResult rayIntersect(Ogre::Ray ray);

        void setHeightFromRays(terrainRays rays, int brushSize, int height);
        void terrainEditFromRays(terrainRays rays, int brushSize, int brushFlow, bool additive, bool update);
        void terrainSmoothFromRays(terrainRays rays, int brushSize);

        void setBlendFromRays(Ogre::TerrainGroup::RayResult centreRay, int brushSize, int brushFlow, int layerIndex, bool additive, bool update, std::vector<terrainTextureCommandInformation> *info = 0);

        void saveTerrains(bool reSave);
        void updateAllTerrains(bool synchronus);

    protected:

    private:
        Ogre::TerrainGlobalOptions* terrainGlobals;
        Ogre::TerrainGroup *terrainGroup;
        Ogre::SceneManager *sceneManager;

        int vertexCount;
        int terrainSize;
        int terrainHeight;
        std::string path;

        void setupTerrainsArray(terrainRays rays, std::vector<Ogre::Terrain*> *terrains);
        bool vectorContains(std::vector<Ogre::Terrain*> *terrains, Ogre::Terrain* terrain);

        void destroyScene();
        void configureTerrainDefaults();
        void checkAndDefineTerrain(int x, int y);
};

#endif // TERRAIN_H
