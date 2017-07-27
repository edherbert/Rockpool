#ifndef TERRAINCOMMAND_H
#define TERRAINCOMMAND_H

#include "Command.h"
#include "../../map/Terrain.h"

class Terrain;

struct terrainRays;

class TerrainCommand : public Command
{
    public:
        TerrainCommand(Terrain *terrain, int brushSize, int brushFlow);
        virtual ~TerrainCommand();

        void pushRay(terrainRays ray);

    protected:
        int brushSize;
        int brushFlow;

        Terrain *terrain;

        std::vector<terrainRays>rays;

    private:
};

#endif // TERRAINCOMMAND_H
