#include "TerrainCommand.h"

TerrainCommand::TerrainCommand(Terrain *terrain, Ogre::Terrain *terr){
    this->terrain = terrain;
    this->terr = terr;
}

TerrainCommand::~TerrainCommand(){

}

void TerrainCommand::checkTerrainSquare(terrainSquareInformation square){
    bool found = true;
    for(int y = square.startY; y < square.endY; y++){
        for(int x = square.startX; x < square.endX; x++){

            bool pointFound = false;
            for(terrainSquareInformation t : squares){
                if(x > t.startX && y > t.startY && x < t.endX && y < t.endY){
                    pointFound = true;
                    break;
                }
            }

            if(!pointFound){
                found = false;
                //This individual point was not found.
                //Get the terrain information for that point.
                collectTerrainInfo(x, y);
            }
        }
    }
    if(!found){
        squares.push_back(square);
    }
}

//Collect the height data, although this is overriden in the texture command.
void TerrainCommand::collectTerrainInfo(int x, int y){
    terrainCommandInformation info;
    info.x = x;
    info.y = y;
    info.height = terr->getHeightAtPoint(x, y);

    previousInformation.push_back(info);
}

void TerrainCommand::pushBrushInformation(terrainBrushInformation info){
    brushInfo.push_back(info);
}
