#include "Map.h"

#include "../ui/Tools/ToolPreferencesHandler.h"
#include "../ui/TerrainInfoHandler.h"
#include "../system/Command/TerrainCommand.h"
#include "../system/Command/TerrainTextureCommand.h"
#include "../system/Command/TerrainEditCommand.h"
#include "../system/Command/Object/ObjectCommand.h"
#include "../system/Command/CommandManager.h"
#include "MapDecal.h"
#include "Terrain.h"
#include "../ui/GLCanvas.h"
#include "Object/Object.h"
#include "../ui/Tools/ToolsPanelHandler.h"
#include "../ui/Hierarchy/ObjectHierarchy.h"
#include "../ui/Hierarchy/HierarchyObjectInformation.h"

#include <wx/treebase.h>

#include "math.h"


Map::Map(HandlerData *handlerData, const std::string& path, mapInformation info){
    this->handlerData = handlerData;
    this->path = path;
    this->mapName = info.mapName;
    this->mapWidth = info.mapWidth;
    this->mapHeight = info.mapHeight;
    this->vertexCount = info.vertexCount;
    this->terrainSize = info.terrainSize;
    this->terrainHeight = info.terrainHeight;
}

Map::~Map(){

}

void Map::start(GLCanvas *canvas){
    this->canvas = canvas;

    sceneManager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, "SceneManager");

    camera = sceneManager->createCamera("Camera");
    camera->setPosition(defaultCameraPosition);
    camera->setDirection(defaultCameraDirection);
    camera->setNearClipDistance(5);

    viewport = canvas->getWindow()->addViewport(camera);

    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    canvas->setViewportSize();

    //sceneManager->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    sceneManager->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    terrain = new Terrain(sceneManager, path, mapName, mapWidth, mapHeight, vertexCount, terrainSize, terrainHeight);

    Ogre::Light* light = sceneManager->createLight("light");
    light->setPosition(20, 80, 50);

    //The map needs a reference to the hierarchy.

    //objectHierarchy->getTree()->get
    Object *rootObject = new Object(sceneManager);
    sceneManager->getRootSceneNode()->addChild(rootObject->getSceneNode());

    HierarchyObjectInformation *info = new HierarchyObjectInformation(rootObject);
    wxTreeItemId root = objectHierarchy->getTree()->GetRootItem();
    objectHierarchy->getTree()->SetItemData(root, info);

    mapStarted = true;
}

Ogre::Camera* Map::getCamera(){
    return camera;
}

Ogre::SceneManager* Map::getSceneManager(){
    return sceneManager;
}

void Map::destroy(){
    sceneManager->destroyAllCameras();
    sceneManager->destroyAllEntities();
    sceneManager->destroyAllLights();
    //The viewport is deleted in the destroyAllCameras bit so don't try to delete that.
    delete sceneManager;
}

bool Map::getMapStarted(){
    return mapStarted;
}

void Map::pointCamera(int xOffset, int yOffset){
    float sense = 0.05;
    float xCamera = xOffset;
    float yCamera = yOffset;
    //xOffset *= sense;
    //yOffset *= sense;
    xCamera *= sense;
    yCamera *= sense;

    yaw += xCamera;
    pitch += yCamera;
    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;

    Ogre::Vector3 front;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));

    //Normalise the camera front
    float length = sqrt((front.x * front.x) + (front.y * front.y) + (front.z * front.z));
    Ogre::Vector3 cameraFront = Ogre::Vector3(front.x / length, front.y / length, front.z / length);

    camera->setDirection(cameraFront);
}

float Map::radians(float value){
    return value * (M_PI / 180);
}

float Map::degrees(float value){
    return value / (M_PI * 180);
}

void Map::updateInput(){
    //Only run if the mouse is within the canvas and it has focus
    //This should not be in-charge of updating logic, only running functions
    //This is because it's not constantly run.
    if(canvas->getKey(KEY_W)) moveCameraPosition(camera->getDirection());
    if(canvas->getKey(KEY_S)) moveCameraPosition(-camera->getDirection());
    if(canvas->getKey(KEY_A)) moveCameraPosition(-camera->getRight());
    if(canvas->getKey(KEY_D)) moveCameraPosition(camera->getRight());

    if(canvas->getKey(KEY_F)) moveCameraPosition(camera->getUp());
    if(canvas->getKey(KEY_G)) moveCameraPosition(-camera->getUp());

    if(canvas->getKey(KEY_M)){
        if(!performingObjectCommand){
            performingObjectCommand = true;
            currentObjectCommand = new ObjectCommand(objectHierarchy->getTree());
        }
    }

    if(performingObjectCommand){
        if(canvas->getKey(KEY_ESCAPE)) performingObjectCommand = false;

        //Create the command in the earlier bit
        //Here I could call something to the command.
        currentObjectCommand->update(canvas->getMouseDiffX(), canvas->getMouseDiffY());
    }else{
        if(canvas->getMouseButton(MOUSE_LEFT)) handleClick(canvas->getMouseX(), canvas->getMouseY(), MOUSE_LEFT);
        if(canvas->getMouseButton(MOUSE_RIGHT)) handleClick(canvas->getMouseX(), canvas->getMouseY(), MOUSE_RIGHT);

        //If neither mouse buttons are pressed
        if(!canvas->getMouseButton(MOUSE_LEFT) && !canvas->getMouseButton(MOUSE_RIGHT)){
            if(currentTerrainCommand){
                handlerData->terrainInfoHandler->getMainFrame()->getMain()->getCommandManager()->pushCommand(currentTerrainCommand);
                currentTerrainCommand = 0;
            }
        }
    }
}

void Map::moveCameraPosition(Ogre::Vector3 ammount){
    Ogre::Vector3 ammountToMove = ammount;
    if(canvas->getKey(wxKeyCode::WXK_SHIFT)){
        ammountToMove *= 9;
    }
    camera->move(ammountToMove);
    canvas->renderFrame();
    updateCursor(canvas->getMouseX(), canvas->getMouseY());
}

Ogre::TerrainGroup::RayResult Map::checkTerrainRayMouse(int x, int y){
    int width, height;
    canvas->GetSize(&width, &height);

    Ogre::Ray ray = camera->getCameraToViewportRay((float)x / (float)width, (float)y / (float)height);

    return terrain->rayIntersect(ray);
}

void Map::updateCursor(int x, int y){
    Ogre::TerrainGroup::RayResult result = checkTerrainRayMouse(x, y);
    if(result.hit){
        handlerData->terrainInfoHandler->setCurrentTerrain(result.terrain);
    }else{
        handlerData->terrainInfoHandler->setCurrentTerrain(0);
    }
}

void Map::handleClick(int x, int y, int mouseButton){
    int currentTool = handlerData->toolPanelHandler->getCurrentTool();
    Ogre::TerrainGroup::RayResult centreResult = checkTerrainRayMouse(x, y);

    handleTerrainTool(centreResult, mouseButton, currentTool);
}

void Map::handleTerrainTool(Ogre::TerrainGroup::RayResult centreRay, int mouseButton, int toolId){
    //If the centre did not land on a terrain, then abort the entire thing.
    if(!centreRay.hit) return;
    int brushSize = 0;
    int brushFlow = 0;
    int layerIndex = 0;

    if(toolId == TOOL_PANEL_TERRAIN_EDIT){
        brushSize = handlerData->toolPreferencesHandler->getTerrainEditTool()->getBrushSize();
        brushFlow = handlerData->toolPreferencesHandler->getTerrainEditTool()->getBrushFlow();
    }else if(toolId == TOOL_PANEL_TERRAIN_HEIGHT){
        brushSize = handlerData->toolPreferencesHandler->getTerrainHeightTool()->getBrushSize();
        //Store the height in the flow to save creating a new variable.
        brushFlow = handlerData->toolPreferencesHandler->getTerrainHeightTool()->getHeight();
    }else if(toolId == TOOL_PANEL_TERRAIN_SMOOTH){
        brushSize = handlerData->toolPreferencesHandler->getTerrainSmoothTool()->getBrushSize();
        brushFlow = handlerData->toolPreferencesHandler->getTerrainSmoothTool()->getBrushFlow();
    }else if(toolId == TOOL_PANEL_TERRAIN_TEXTURE){
        brushSize = handlerData->toolPreferencesHandler->getTerrainTextureTool()->getBrushSize();
        brushFlow = handlerData->toolPreferencesHandler->getTerrainTextureTool()->getBrushFlow();
        layerIndex = handlerData->toolPreferencesHandler->getTerrainTextureTool()->getCurrentTerrainTextureID();
    }

    if(!currentTerrainCommand){
        if(toolId == TOOL_PANEL_TERRAIN_TEXTURE){
            currentTerrainCommand = new TerrainTextureCommand(terrain, centreRay.terrain, layerIndex);
        }else{
            currentTerrainCommand = new TerrainEditCommand(terrain, centreRay.terrain, toolId);
        }
    }
    if(currentTerrainCommand){
        terrainSquareInformation squareInfo = genSquareInfo(centreRay.terrain, centreRay.position.x, centreRay.position.y, centreRay.position.z, brushSize, toolId == TOOL_PANEL_TERRAIN_TEXTURE);

        terrainBrushInformation brushInfo = {squareInfo, brushSize, brushFlow};
        currentTerrainCommand->pushBrushInformation(brushInfo);

        //Clean this up at some point
        squareInfo.startX -= 1;
        squareInfo.startY -= 1;
        squareInfo.endX += 1;
        squareInfo.endY += 1;

        currentTerrainCommand->checkTerrainSquare(squareInfo);

        squareInfo.startX += 1;
        squareInfo.startY += 1;
        squareInfo.endX -= 1;
        squareInfo.endY -= 1;

        if(toolId == TOOL_PANEL_TERRAIN_EDIT) terrain->terrainEditFromBrush(centreRay.terrain, brushInfo, true);
        if(toolId == TOOL_PANEL_TERRAIN_HEIGHT) terrain->terrainHeightFromBrush(centreRay.terrain, brushInfo, true);
        if(toolId == TOOL_PANEL_TERRAIN_SMOOTH) terrain->terrainSmoothFromBrush(centreRay.terrain, brushInfo, true);
        if(toolId == TOOL_PANEL_TERRAIN_TEXTURE) terrain->terrainTextureFromBrush(centreRay.terrain, brushInfo, layerIndex, true);
    }

    canvas->renderFrame();
}

terrainSquareInformation Map::genSquareInfo(Ogre::Terrain *terr, int x, int y, int z, int brushSize, bool textureTool){
    int brushDiv = brushSize / 2;

    long startX = x - brushDiv;
    long startZ = z - brushDiv;
    long endX = x + brushDiv;
    long endZ = z + brushDiv;

    Ogre::uint16 terrainSize;
    if(textureTool){
        terrainSize = terr->getLayerBlendMapSize();
    }else{
        terrainSize = terr->getSize() - 1;
    }

    Ogre::Vector3 terrainStart;
    Ogre::Vector3 terrainEnd;
    Ogre::Vector3 terrainCentre;

    terr->getTerrainPosition(startX, y, startZ, &terrainStart);
    terr->getTerrainPosition(endX, y, endZ, &terrainEnd);
    terr->getTerrainPosition(x, y, z, &terrainCentre);

    terrainStart *= terrainSize;
    terrainEnd *= terrainSize;
    terrainCentre *= terrainSize;

    terrainSquareInformation squareInfo;
    squareInfo.startX = terrainStart.x;
    squareInfo.endX = terrainEnd.x;
    squareInfo.centreX = terrainCentre.x;


    if(textureTool){
        squareInfo.centreY = terrainSize - terrainCentre.y;
        squareInfo.endY = terrainSize - terrainEnd.y;
        squareInfo.startY = terrainSize - terrainStart.y;
    }else{
        squareInfo.centreY = terrainCentre.y;
        //These are flipped for the regular squares, because the numbers that they represent are flipped on the terrain.
        squareInfo.endY = terrainStart.y;
        squareInfo.startY = terrainEnd.y;
    }

    return squareInfo;
}

mapInformation Map::getMapInformation(){
    mapInformation info;
    info.mapName = mapName;
    info.mapWidth = mapWidth;
    info.mapHeight = mapHeight;
    info.vertexCount = vertexCount;
    info.terrainSize = terrainSize;
    info.terrainHeight = terrainHeight;

    return info;
}

void Map::saveMap(bool reSave){
    terrain->saveTerrains(reSave);
}

void Map::setDefaultCameraValues(Ogre::Vector3 cameraPosition, Ogre::Vector3 cameraDirection){
    this->defaultCameraPosition = cameraPosition;
    this->defaultCameraDirection = cameraDirection;
}

void Map::setObjectHierarchy(ObjectHierarchy *objectHierarchy){
    this->objectHierarchy = objectHierarchy;
}
