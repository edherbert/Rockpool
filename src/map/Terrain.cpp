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

void Terrain::setHeightFromRays(Ogre::TerrainGroup::RayResult centreRay,
Ogre::TerrainGroup::RayResult leftTopResult,
Ogre::TerrainGroup::RayResult rightTopResult,
Ogre::TerrainGroup::RayResult leftBottomResult,
Ogre::TerrainGroup::RayResult rightBottomResult, int brushSize, int brushFlow){

    //An array to contain the terrains that need to be edited
    std::vector<Ogre::Terrain*>terrains;

    //Determine which terrains need to be edited
    //If the terrain needs to be added to the vector and is not already in it.
    if(leftTopResult.hit && !vectorContains(&terrains, leftTopResult.terrain)) terrains.push_back(leftTopResult.terrain);
    if(rightTopResult.hit && !vectorContains(&terrains, rightTopResult.terrain)) terrains.push_back(rightTopResult.terrain);
    if(leftBottomResult.hit && !vectorContains(&terrains, leftBottomResult.terrain)) terrains.push_back(leftBottomResult.terrain);
    if(rightBottomResult.hit && !vectorContains(&terrains, rightBottomResult.terrain)) terrains.push_back(rightBottomResult.terrain);

    //Create the other points as a square of the brush size
    Ogre::Vector3 centrePos = centreRay.position;
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

                float newHeight = terrain->getHeightAtPoint(x, y) + 0.05 * brushFlow;
                terrain->setHeightAtPoint(x, y, newHeight);
            }
        }

    }
    terrainGroup->update();
}

void Terrain::setBlendFromRays(Ogre::TerrainGroup::RayResult centreRay, int brushSize, int brushFlow, int layerIndex){
    int brushDiv = brushSize / 2;

    long startX = centreRay.position.x - brushDiv;
    long startZ = centreRay.position.z - brushDiv;
    long endX = centreRay.position.x + brushDiv;
    long endZ = centreRay.position.z + brushDiv;

    Ogre::uint16 terrainSize = centreRay.terrain->getLayerBlendMapSize();

    Ogre::Vector3 terrainStart;
    Ogre::Vector3 terrainEnd;

    centreRay.terrain->getTerrainPosition(startX, centreRay.position.y, startZ, &terrainStart);
    centreRay.terrain->getTerrainPosition(endX, centreRay.position.y, endZ, &terrainEnd);

    terrainStart *= terrainSize;
    terrainEnd *= terrainSize;
    for(Ogre::uint8 t = 1; t < centreRay.terrain->getLayerCount(); t++){
        Ogre::TerrainLayerBlendMap *layer = centreRay.terrain->getLayerBlendMap(t);

        int val = 0;
        if(t == layerIndex) val = 1;

        for(long y = terrainEnd.y; y < terrainStart.y; y++){
            for(long x = terrainStart.x; x < terrainEnd.x; x++){
                long yval = terrainSize - y;
                if(x < 0 || yval < 0 || x > terrainSize || yval > terrainSize) continue;

                layer->setBlendValue(x, yval, val);
            }
        }
        layer->update();
    }

    //I think it would need to loop through each layer, doing the oposite of the function to the layer that it is not.
    //So by adding to layer 2, you would be removing the same ammount being added from layers 1 and 3
    //Remember that layer 0 cannot be altered, as it will always have 100%
}


void Terrain::saveTerrains(bool reSave){
    terrainGroup->saveAllTerrains(!reSave);
}
