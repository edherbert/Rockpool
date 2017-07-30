#ifndef TERRAINCOMMAND_H
#define TERRAINCOMMAND_H

#include "Command.h"
#include "../../map/Terrain.h"

class Terrain;

struct terrainRays;

class TerrainCommand : public Command
{
    public:
        TerrainCommand(Terrain *terrain, Ogre::Terrain *terr);
        virtual ~TerrainCommand();

        void pushRay(terrainRays ray);

        void checkTerrainSquare(terrainSquareInformation square);
        void pushBrushInformation(terrainBrushInformation brushInfo);

        virtual void collectTerrainInfo(int x, int y);

    protected:
        Terrain *terrain;
        Ogre::Terrain *terr;

        std::vector<terrainBrushInformation>brushInfo;
        std::vector<terrainSquareInformation>squares;
        std::vector<terrainCommandInformation>previousInformation;

    private:
};

#endif // TERRAINCOMMAND_H
