#include "TerrainEditCommand.h"

TerrainEditCommand::TerrainEditCommand(Terrain *terrain, int brushSize, int brushFlow) : TerrainCommand(terrain, brushSize, brushFlow){

}

TerrainEditCommand::~TerrainEditCommand(){

}

void TerrainEditCommand::performAction(){
    for(terrainRays ray : rays){
        terrain->terrainEditFromRays(ray, brushSize, brushFlow, true, false);
    }
    terrain->updateAllTerrains(true);
}

void TerrainEditCommand::performAntiAction(){
    for(terrainRays ray : rays){
        terrain->terrainEditFromRays(ray, brushSize, brushFlow, false, false);
    }
    terrain->updateAllTerrains(true);
}
