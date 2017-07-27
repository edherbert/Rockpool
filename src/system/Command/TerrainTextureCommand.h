#ifndef TERRAINTEXTURECOMMAND_H
#define TERRAINTEXTURECOMMAND_H

#include "TerrainCommand.h"

class TerrainTextureCommand : public TerrainCommand
{
    public:
        TerrainTextureCommand(Terrain *terrain, int brushSize, int brushFlow, int layerIndex);
        virtual ~TerrainTextureCommand();

        void performAction();
        void performAntiAction();

        void pushTextureInfo(std::vector <terrainTextureCommandInformation> info);

    protected:

    private:
        int layerIndex = 0;

        //std::vector<terrainTextureCommandInformation> textureInfo;
        //A vector that contains squares of terrain texture information
        std::vector<std::vector<terrainTextureCommandInformation>> textureInfo;
};

#endif // TERRAINTEXTURECOMMAND_H
