#include "TerrainEditCommand.h"

TerrainEditCommand::TerrainEditCommand(Terrain *terrain, Ogre::Terrain *terr) : TerrainCommand(terrain, terr){

}

TerrainEditCommand::~TerrainEditCommand(){

}

void TerrainEditCommand::performAction(){
    for(terrainBrushInformation info : brushInfo){
        terrain->terrainEditFromBrush(terr, info, false);
    }
    terr->update(true);
}

void TerrainEditCommand::performAntiAction(){
    for(terrainCommandInformation info : previousInformation){
        terr->setHeightAtPoint(info.x, info.y, info.height);
    }
    terr->update(true);
}
