#include "TerrainTextureCommand.h"

TerrainTextureCommand::TerrainTextureCommand(Terrain *terrain, int brushSize, int brushFlow, int layerIndex) : TerrainCommand(terrain, brushSize, brushFlow){
    this->layerIndex = layerIndex;
}

TerrainTextureCommand::~TerrainTextureCommand(){

}

void TerrainTextureCommand::performAction(){
    for(terrainRays ray : rays){
        terrain->setBlendFromRays(ray.centreRay, brushSize, brushFlow, layerIndex, true, false);
    }

    Ogre::Terrain *temp = rays[0].centreRay.terrain;

    for(Ogre::uint8 t = 1; t < temp->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = temp->getLayerBlendMap(t);

        layer->update();
    }
}

void TerrainTextureCommand::performAntiAction(){
    for(terrainRays ray : rays){
        terrain->setBlendFromRays(ray.centreRay, brushSize, brushFlow, layerIndex, false, false);
    }

    Ogre::Terrain *temp = rays[0].centreRay.terrain;

    for(Ogre::uint8 t = 1; t < temp->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = temp->getLayerBlendMap(t);

        layer->update();
    }
}
