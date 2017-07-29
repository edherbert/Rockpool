#ifndef TERRAINTEXTURECOMMAND_H
#define TERRAINTEXTURECOMMAND_H

#include "TerrainCommand.h"

struct textureRayInfo{
    Ogre::TerrainGroup::RayResult ray;
    int brushSize;
    int brushFlow;
};

class TerrainTextureCommand : public TerrainCommand
{
    public:
        TerrainTextureCommand(Terrain *terrain, int brushSize, int brushFlow, int layerIndex);
        virtual ~TerrainTextureCommand();

        void performAction();
        void performAntiAction();

        void collectTerrainInfo(int x, int y, Ogre::Terrain *terr);

        void cleanupTemporaryResources();

        void pushTextureRay(Ogre::TerrainGroup::RayResult ray, int brushSize, int brushFlow);

    protected:

    private:
        int layerIndex = 0;

        Ogre::Terrain *actualTerrain = 0;

        std::vector<terrainTextureCommandInformation> textureInfo;
        std::vector<textureRayInfo> textureRays;
};

#endif // TERRAINTEXTURECOMMAND_H
