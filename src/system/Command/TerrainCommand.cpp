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
