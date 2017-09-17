#include "Terrain.h"

Terrain::Terrain(Ogre::SceneManager *sceneManager, std::string path, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight){
    this->path = path;
    this->sceneManager = sceneManager;
    this->vertexCount = vertexCount;
    this->terrainSize = terrainSize;
    this->terrainHeight = terrainHeight;

    terrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

    terrainGroup = OGRE_NEW Ogre::TerrainGroup(sceneManager, Ogre::Terrain::ALIGN_X_Z, vertexCount, terrainSize);
    //Maybe change this with the save function
    terrainGroup->setFilenameConvention(Ogre::String(path + "/terrainDat/" + mapName), Ogre::String("dat"));
    terrainGroup->setOrigin(Ogre::Vector3::ZERO);

    configureTerrainDefaults();


    for(int x = 0; x < mapWidth; ++x){
        for(int y = 0; y < mapHeight; ++y){
            //All terrains are defined at the beginning.
            //They are loaded and un-loaded when needed because when un-loaded no data is stored in memory.
            checkAndDefineTerrain(x, y);
        }
    }

    if(TERRAIN_ENABLED){
        terrainGroup->loadAllTerrains(true);
        terrainGroup->freeTemporaryResources();
        terrainGroup->saveAllTerrains(true);
    }
}

Terrain::~Terrain(){
    destroyScene();
}

void Terrain::checkAndDefineTerrain(int x, int y){
    Ogre::String filename = terrainGroup->generateFilename(x, y);
    if(Ogre::ResourceGroupManager::getSingleton().resourceExists(terrainGroup->getResourceGroup(), filename)){
        terrainGroup->defineTerrain(x, y, filename);
    }else{
        terrainGroup->defineTerrain(x, y, 0.0f);
    }
}

void Terrain::configureTerrainDefaults(){
    terrainGlobals->setMaxPixelError(8);
    terrainGlobals->setCompositeMapDistance(9000);

    Ogre::Terrain::ImportData& importData = terrainGroup->getDefaultImportSettings();
    importData.terrainSize = vertexCount;
    importData.worldSize = terrainSize;
    importData.inputScale = terrainHeight;
    importData.minBatchSize = 33;
    importData.maxBatchSize = 65;

    importData.layerList.resize(4);
    importData.layerList[0].worldSize = 100;
    importData.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    importData.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");

    importData.layerList[1].worldSize = 100;
    importData.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    importData.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
}

void Terrain::destroyScene(){
    OGRE_DELETE terrainGroup;
    OGRE_DELETE terrainGlobals;
}

Ogre::TerrainGroup::RayResult Terrain::rayIntersect(Ogre::Ray ray){
    return terrainGroup->rayIntersects(ray);
}

void Terrain::terrainTextureFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, int layerIndex, bool update){
    Ogre::uint16 terrainSize = terr->getLayerBlendMapSize();
    float brushSize = ((brushInfo.square.endX - brushInfo.square.startX)/2);
    for(Ogre::uint8 t = 1; t < terr->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = terr->getLayerBlendMap(t);
        for(long y = brushInfo.square.startY; y < brushInfo.square.endY; y++){
            for(long x = brushInfo.square.startX; x < brushInfo.square.endX; x++){
                if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;

                float distance = sqrt(pow(brushInfo.square.centreY - y, 2) + pow(brushInfo.square.centreX - x, 2));
                if(distance <= brushSize){
                    distance /= brushSize;
                    distance = 1 - distance;
                    distance = distance * distance;
                }else{
                    distance = 0;
                }

                float currentValue = layer->getBlendValue(x, y);
                float ammountToAdd = 0;
                if(t == layerIndex){
                    ammountToAdd +=  0.005 * brushInfo.brushFlow * distance;
                }else{
                    ammountToAdd -= 0.005 * brushInfo.brushFlow * distance;
                }

                currentValue += ammountToAdd;
                if(currentValue < 0) currentValue = 0;
                if(currentValue > 1) currentValue = 1;

                layer->setBlendValue(x, y, currentValue);
            }
        }
        if(update) layer->update();
    }

}

void Terrain::terrainEditFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update){
    float brushSize = ((brushInfo.square.endX - brushInfo.square.startX)/2);
    for(long y = brushInfo.square.startY; y < brushInfo.square.endY; y++){
        for(long x = brushInfo.square.startX; x < brushInfo.square.endX; x++){
            if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;
            float distance = sqrt(pow(brushInfo.square.centreY - y, 2) + pow(brushInfo.square.centreX - x, 2));
            if(distance <= brushSize){
                distance /= brushSize;
                distance = 1 - distance;
                distance = distance * distance;
            }else{
                distance = 0;
            }

            float current = terr->getHeightAtPoint(x, y);
            float ammountToAdd = 0.05 * brushInfo.brushFlow * distance;
            terr->setHeightAtPoint(x, y, current + ammountToAdd);
        }
    }
    if(update)terrainGroup->update();
}

void Terrain::terrainHeightFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update){
    for(long y = brushInfo.square.startY; y < brushInfo.square.endY; y++){
        for(long x = brushInfo.square.startX; x < brushInfo.square.endX; x++){
            if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;

            terr->setHeightAtPoint(x, y, brushInfo.brushFlow);
        }
    }
    if(update)terrainGroup->update();
}

void Terrain::terrainSmoothFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, bool update){
    for(long y = brushInfo.square.startY; y < brushInfo.square.endY; y++){
        for(long x = brushInfo.square.startX; x < brushInfo.square.endX; x++){
            if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;

            //The total height
            float total = 0;
            //The number of points checked
            int totalAmmount = 0;
            //+ and - 1 to get the range of values around the point.
            for(long yy = y - 1; yy <= y + 1; yy++){
                for(long xx = x - 1; xx <= x + 1; xx++){
                    if(xx < 0 || yy < 0 || xx > terrainSize || yy > terrainSize) continue;
                    total += terr->getHeightAtPoint(xx, yy);
                    totalAmmount++;
                }
            }
            total /= totalAmmount;

            terr->setHeightAtPoint(x, y, total);
        }
    }
    if(update)terr->update();
}

void Terrain::saveTerrains(bool reSave){
    terrainGroup->saveAllTerrains(!reSave);
}

void Terrain::updateAllTerrains(bool synchronus){
    terrainGroup->update(synchronus);
}
