#include "TerrainTextureCommand.h"

TerrainTextureCommand::TerrainTextureCommand(Terrain *terrain, Ogre::Terrain *terr, int layerIndex) : TerrainCommand(terrain, terr){
    this->layerIndex = layerIndex;
}

TerrainTextureCommand::~TerrainTextureCommand(){

}

void TerrainTextureCommand::performAction(){
    for(terrainBrushInformation info : brushInfo){
        terrain->setBlendFromBrush(terr, info, layerIndex, false);
    }

    for(Ogre::uint8 t = 1; t < terr->getLayerCount(); t++){
        terr->getLayerBlendMap(t)->update();
    }
}

void TerrainTextureCommand::performAntiAction(){
    for(int i = 1; i < (int)terr->getLayerCount(); i++){
        Ogre::TerrainLayerBlendMap *layer = terr->getLayerBlendMap(i);
        for(terrainTextureCommandInformation info : previousTextureInformation){
            layer->setBlendValue(info.x, info.y, info.data[i - 1]);
        }
        layer->update();
    }
}

void TerrainTextureCommand::collectTerrainInfo(int x, int y){
    terrainTextureCommandInformation info;
    info.x = x;
    info.y = y;

    //Remember that info.data[0] represents layer 1, as layer 0 can't be textured
    for(int i = 1; i < (sizeof(info.data) / sizeof(float)) + 1; i++){
        info.data[i - 1] = terr->getLayerBlendMap(i)->getBlendValue(x, y);
    }

    previousTextureInformation.push_back(info);
}

void TerrainTextureCommand::cleanupTemporaryResources(){
    squares.clear();
}
