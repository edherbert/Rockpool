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

    protected:

    private:
        int layerIndex = 0;
};

#endif // TERRAINTEXTURECOMMAND_H
