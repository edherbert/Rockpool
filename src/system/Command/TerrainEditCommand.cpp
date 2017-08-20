#include "TerrainEditCommand.h"

#include "../../map/Terrain.h"

TerrainEditCommand::TerrainEditCommand(Terrain *terrain, Ogre::Terrain *terr, int toolId) : TerrainCommand(terrain, terr){
    this->toolId = toolId;
}

TerrainEditCommand::~TerrainEditCommand(){

}

void TerrainEditCommand::performAction(){
    for(terrainBrushInformation info : brushInfo){
        if(toolId == TOOL_PANEL_TERRAIN_EDIT)terrain->terrainEditFromBrush(terr, info, false);
        if(toolId == TOOL_PANEL_TERRAIN_HEIGHT)terrain->terrainHeightFromBrush(terr, info, false);
        if(toolId == TOOL_PANEL_TERRAIN_SMOOTH)terrain->terrainSmoothFromBrush(terr, info, false);
    }
    terr->update(true);
}

void TerrainEditCommand::performAntiAction(){
    for(terrainCommandInformation info : previousInformation){
        terr->setHeightAtPoint(info.x, info.y, info.height);
    }
    terr->update(true);
}
