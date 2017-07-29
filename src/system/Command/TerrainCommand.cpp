#include "TerrainCommand.h"

TerrainCommand::TerrainCommand(Terrain *terrain, int brushSize, int brushFlow){
    this->terrain = terrain;
    this->brushSize = brushSize;
    this->brushFlow = brushFlow;
}

TerrainCommand::~TerrainCommand(){

}

void TerrainCommand::pushRay(terrainRays ray){
    rays.push_back(ray);
}

void TerrainCommand::checkTerrainSquare(terrainSquareInformation square, Ogre::Terrain *terr){
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
                this->collectTerrainInfo(x, y, terr);
            }
        }
    }
    if(!found){
        squares.push_back(square);
    }
}

void TerrainCommand::collectTerrainInfo(int x, int y, Ogre::Terrain *terr){

}
