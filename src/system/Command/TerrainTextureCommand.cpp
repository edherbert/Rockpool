#include "TerrainTextureCommand.h"

TerrainTextureCommand::TerrainTextureCommand(Terrain *terrain, int brushSize, int brushFlow, int layerIndex) : TerrainCommand(terrain, brushSize, brushFlow){
    //Remove the brush size and flow from here and the other terrain commands
    this->layerIndex = layerIndex;
}

TerrainTextureCommand::~TerrainTextureCommand(){

}

void TerrainTextureCommand::performAction(){
    for(textureRayInfo info : textureRays){
        terrain->setBlendFromRays(info.ray, info.brushSize, info.brushFlow, layerIndex, true, false);
    }

    for(Ogre::uint8 t = 1; t < actualTerrain->getLayerCount(); t++){
        actualTerrain->getLayerBlendMap(t)->update();
    }
}

void TerrainTextureCommand::performAntiAction(){
    for(int i = 1; i < (int)actualTerrain->getLayerCount(); i++){
        Ogre::TerrainLayerBlendMap *layer = actualTerrain->getLayerBlendMap(i);
        for(terrainTextureCommandInformation info : textureInfo){
            layer->setBlendValue(info.x, info.y, info.data[i - 1]);
        }
        layer->update();
    }
}

void TerrainTextureCommand::collectTerrainInfo(int x, int y, Ogre::Terrain *terr){
    actualTerrain = terr;
    terrainTextureCommandInformation info;
    info.x = x;
    info.y = y;

    //Remember that info.data[0] represents layer 1, as layer 0 can't be textured
    for(int i = 1; i < (sizeof(info.data) / sizeof(float)) + 1; i++){
        info.data[i - 1] = terr->getLayerBlendMap(i)->getBlendValue(x, y);
    }

    textureInfo.push_back(info);
}

void TerrainTextureCommand::cleanupTemporaryResources(){
    squares.clear();
}

void TerrainTextureCommand::pushTextureRay(Ogre::TerrainGroup::RayResult ray, int brushSize, int brushFlow){
    textureRayInfo info = {ray, brushSize, brushFlow};

    textureRays.push_back(info);
}
