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

    terrainGroup->loadAllTerrains(true);

    terrainGroup->freeTemporaryResources();

    terrainGroup->saveAllTerrains(true);
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

bool Terrain::vectorContains(std::vector<Ogre::Terrain*> *terrains, Ogre::Terrain* terrain){
    bool found = false;
    for(int i = 0; i < terrains->size(); i++){
        if(terrains->at(i) == terrain) found = true;
    }
    return found;
}

void Terrain::setupTerrainsArray(terrainRays rays, std::vector<Ogre::Terrain*> *terrains){
    if(rays.leftTop.hit && !vectorContains(terrains, rays.leftTop.terrain)) terrains->push_back(rays.leftTop.terrain);
    if(rays.rightTop.hit && !vectorContains(terrains, rays.rightTop.terrain)) terrains->push_back(rays.rightTop.terrain);
    if(rays.leftBottom.hit && !vectorContains(terrains, rays.leftBottom.terrain)) terrains->push_back(rays.leftBottom.terrain);
    if(rays.rightBottom.hit && !vectorContains(terrains, rays.rightBottom.terrain)) terrains->push_back(rays.rightBottom.terrain);
}

void Terrain::setHeightFromRays(terrainRays rays, int brushSize, int height){
    std::vector<Ogre::Terrain*>terrains;

    setupTerrainsArray(rays, &terrains);

    //Create the other points as a square of the brush size
    Ogre::Vector3 centrePos = rays.centreRay.position;
    long startX = centrePos.x - brushSize / 2;
    long startZ = centrePos.z - brushSize / 2;
    long endX = centrePos.x + brushSize / 2;
    long endZ = centrePos.z + brushSize / 2;

    for(Ogre::Terrain *terrain : terrains){
        Ogre::Real terrainSize = (terrain->getSize() - 1);
        Ogre::Vector3 terrainStart;
        Ogre::Vector3 terrainEnd;
        terrain->getTerrainPosition(startX, centrePos.y, startZ, &terrainStart);
        terrain->getTerrainPosition(endX, centrePos.y, endZ, &terrainEnd);

        terrainStart *= terrainSize;
        terrainEnd *= terrainSize;
        //These values are in terrain positions so don't worry if they seem to be smaller than the brush size

        //Flip the values for the y because the start is at the top so this way the start would always have a higher value than the end, thus causing the loop not to run.
        for(long y = terrainEnd.y; y < terrainStart.y; y++){
            for(long x = terrainStart.x; x < terrainEnd.x; x++){
                if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;

                terrain->setHeightAtPoint(x, y, height);
            }
        }

    }
    terrainGroup->update();
}

void Terrain::terrainEditFromRays(terrainRays rays, int brushSize, int brushFlow, bool additive, bool update){
    //An array to contain all the terrains that need to be edited.
    std::vector<Ogre::Terrain*>terrains;

    setupTerrainsArray(rays, &terrains);

    //Create the other points as a square of the brush size
    Ogre::Vector3 centrePos = rays.centreRay.position;
    long startX = centrePos.x - brushSize / 2;
    long startZ = centrePos.z - brushSize / 2;
    long endX = centrePos.x + brushSize / 2;
    long endZ = centrePos.z + brushSize / 2;

    for(Ogre::Terrain *terrain : terrains){
        Ogre::Real terrainSize = (terrain->getSize() - 1);
        //The values of the terrain
        Ogre::Vector3 terrainStart;
        Ogre::Vector3 terrainEnd;
        Ogre::Vector3 terrainCentre;
        terrain->getTerrainPosition(startX, centrePos.y, startZ, &terrainStart);
        terrain->getTerrainPosition(endX, centrePos.y, endZ, &terrainEnd);
        terrain->getTerrainPosition(centrePos.x, centrePos.y, centrePos.z, &terrainCentre);

        //Convert the values from between 0 and 1 into terrain cordinates (0 to terrain size)
        terrainStart *= terrainSize;
        terrainEnd *= terrainSize;
        terrainCentre *= terrainSize;
        //These values are in terrain positions so don't worry if they seem to be smaller than the brush size

        //Flip the values for the y because the start is at the top so this way the start would always have a higher value than the end, thus causing the loop not to run.
        for(long y = terrainEnd.y; y < terrainStart.y; y++){
            for(long x = terrainStart.x; x < terrainEnd.x; x++){
                if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;
                Ogre::Real distance = sqrt(pow(terrainCentre.y - y, 2) + pow(terrainCentre.x - x, 2)) / brushSize;
                //Get the values between 0 and 1
                distance *= 10;
                //Take it from one, so that the closer to the centre, the highter the value.
                distance = 1 - distance;
                //This makes the number closer to the centre higher, and the ones in the radius lower.
                distance = distance * distance;

                float current = terrain->getHeightAtPoint(x, y);
                float ammountToAdd = 0.05 * brushFlow * distance;
                if(!additive)ammountToAdd *= -1;
                terrain->setHeightAtPoint(x, y, current + ammountToAdd);
            }
        }

    }
    if(update)terrainGroup->update();
}

void Terrain::terrainSmoothFromRays(terrainRays rays, int brushSize){
    std::vector<Ogre::Terrain*>terrains;

    setupTerrainsArray(rays, &terrains);

    Ogre::Vector3 centrePos = rays.centreRay.position;
    long startX = centrePos.x - brushSize / 2;
    long startZ = centrePos.z - brushSize / 2;
    long endX = centrePos.x + brushSize / 2;
    long endZ = centrePos.z + brushSize / 2;

    for(Ogre::Terrain *terrain : terrains){
        Ogre::Real terrainSize = (terrain->getSize() - 1);
        Ogre::Vector3 terrainStart;
        Ogre::Vector3 terrainEnd;
        Ogre::Vector3 terrainCentre;
        terrain->getTerrainPosition(startX, centrePos.y, startZ, &terrainStart);
        terrain->getTerrainPosition(endX, centrePos.y, endZ, &terrainEnd);
        terrain->getTerrainPosition(centrePos.x, centrePos.y, centrePos.z, &terrainCentre);

        terrainStart *= terrainSize;
        terrainEnd *= terrainSize;
        terrainCentre *= terrainSize;
        for(long y = terrainEnd.y; y < terrainStart.y; y++){
            for(long x = terrainStart.x; x < terrainEnd.x; x++){
                if(x < 0 || y < 0 || x > terrainSize || y > terrainSize) continue;

                float total = 0;
                int totalAmmount = 0;
                for(long yy = y - 1; yy <= y + 1; yy++){
                    for(long xx = x - 1; xx <= x + 1; xx++){
                        if(xx < 0 || yy < 0 || xx > terrainSize || yy > terrainSize) continue;
                        total += terrain->getHeightAtPoint(xx, yy);
                        totalAmmount++;
                    }
                }
                total /= totalAmmount;

                terrain->setHeightAtPoint(x, y, total);
            }
        }

    }
    terrainGroup->update();
}


void Terrain::setBlendFromBrush(Ogre::Terrain *terr, terrainBrushInformation brushInfo, int layerIndex, bool update){
    float brushSize = ((brushInfo.square.endX - brushInfo.square.startX)/2);
    for(Ogre::uint8 t = 1; t < terr->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = terr->getLayerBlendMap(t);
        for(long y = brushInfo.square.startY; y < brushInfo.square.endY; y++){
            for(long x = brushInfo.square.startX; x < brushInfo.square.endX; x++){
            //Check whether the terrain size works properly.
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
    for(long y = brushInfo.square.endY; y < brushInfo.square.startY; y++){
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

void Terrain::saveTerrains(bool reSave){
    terrainGroup->saveAllTerrains(!reSave);
}

void Terrain::updateAllTerrains(bool synchronus){
    terrainGroup->update(synchronus);
}
