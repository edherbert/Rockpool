#ifndef TERRAINTEXTURECOMMAND_H
#define TERRAINTEXTURECOMMAND_H

#include "TerrainCommand.h"

/*struct textureRayInfo{
    Ogre::TerrainGroup::RayResult ray;
    int brushSize;
    int brushFlow;
};*/

class TerrainTextureCommand : public TerrainCommand
{
    public:
        TerrainTextureCommand(Terrain *terrain, Ogre::Terrain *terr, int layerIndex);
        virtual ~TerrainTextureCommand();

        void performAction();
        void performAntiAction();

        void collectTerrainInfo(int x, int y);

        void cleanupTemporaryResources();

        //void pushTextureRay(Ogre::TerrainGroup::RayResult ray, int brushSize, int brushFlow);

    protected:

    private:
        int layerIndex = 0;

        std::vector<terrainTextureCommandInformation> previousTextureInformation;
        //std::vector<textureRayInfo> textureRays;
};

#endif // TERRAINTEXTURECOMMAND_H
