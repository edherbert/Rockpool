#include "TerrainTextureCommand.h"

TerrainTextureCommand::TerrainTextureCommand(Terrain *terrain, int brushSize, int brushFlow, int layerIndex) : TerrainCommand(terrain, brushSize, brushFlow){
    this->layerIndex = layerIndex;
}

TerrainTextureCommand::~TerrainTextureCommand(){

}

void TerrainTextureCommand::performAction(){
    /*for(terrainRays ray : rays){
        terrain->setBlendFromRays(ray.centreRay, brushSize, brushFlow, layerIndex, true, false);
    }

    Ogre::Terrain *temp = rays[0].centreRay.terrain;

    for(Ogre::uint8 t = 1; t < temp->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = temp->getLayerBlendMap(t);

        layer->update();
    }*/
}

void TerrainTextureCommand::performAntiAction(){
    Ogre::Terrain *temp = rays[0].centreRay.terrain;
    Ogre::TerrainLayerBlendMap *layer1 = temp->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap *layer2 = temp->getLayerBlendMap(2);
    Ogre::TerrainLayerBlendMap *layer3 = temp->getLayerBlendMap(3);
    for(int g = textureInfo.size() - 1; g >= 0; g--){
        std::vector<terrainTextureCommandInformation> grids = textureInfo.at(g);
        for(int i = grids.size() - 1; i >= 0; i--){
            terrainTextureCommandInformation info = grids.at(i);

            //Loop through the data list backwards and set the values for each layer, then update the terrains.
            layer1->setBlendValue(info.x, info.y, info.layer1);
            layer2->setBlendValue(info.x, info.y, info.layer2);
            layer3->setBlendValue(info.x, info.y, info.layer3);
        }
    }
    layer1->update();
    layer2->update();
    layer3->update();
}

void TerrainTextureCommand::pushTextureInfo(std::vector <terrainTextureCommandInformation> info){
    textureInfo.push_back(info);
}

//Create a function that checks the squares. This can be inherited from the terrain command.
