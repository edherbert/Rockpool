#ifndef TERRAINCOMMAND_H
#define TERRAINCOMMAND_H

#include "Command.h"

#include <Ogre.h>
#include <Terrain/OgreTerrainGroup.h>
#include <vector>

class Terrain;

struct terrainRays;

struct terrainTextureCommandInformation;
struct terrainCommandInformation;
struct terrainSquareInformation;
struct terrainBrushInformation;

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
