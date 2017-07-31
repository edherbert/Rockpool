#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <Ogre.h>

#include <cmath>
#include <vector>

//Contains the previous information for the terrain texture
struct terrainTextureCommandInformation{
    int x;
    int y;
    float data[3];
};

//Contains the previous information for the terrain height
struct terrainCommandInformation{
    int x;
    int y;
    float height;
};

//Used to store the position of the terrain brush in terrain space.
//It's also used to check whether a point of terrain needs it's data added to the terrain information list.
struct terrainSquareInformation{
    int startX;
    int startY;
    int endX;
    int endY;
    int centreX;
    int centreY;
};

//Used to contain information about brush strokes.
//Mostly used to re-do functions in the command manager.
struct terrainBrushInformation{
    terrainSquareInformation square;
    int brushSize;
    int brushFlow;
};

class Terrain
{
    public:
        Terrain(Ogre::SceneManager *sceneManager, std::string path, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);
        virtual ~Terrain();

        Ogre::TerrainGroup::RayResult rayIntersect(Ogre::Ray ray);

        void terrainTextureFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, int layerIndex, bool update);
        void terrainEditFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update);
        void terrainHeightFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update);
        void terrainSmoothFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update);

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

        void destroyScene();
        void configureTerrainDefaults();
        void checkAndDefineTerrain(int x, int y);
};

#endif // TERRAIN_H
