#ifndef MAP_H
#define MAP_H

#include "../ui/GLCanvas.h"
#include <OGRE/Ogre.h>
#include "Terrain.h"
#include "MapDecal.h"

#include "math.h"
#include "../ui/Tools/ToolPreferencesHandler.h"
#include "../ui/TerrainInfoHandler.h"

class GLCanvas;
class ToolPreferencesHandler;
class TerrainInfoHandler;

struct HandlerData;
struct mapInformation;

class Map
{
    public:
        Map(HandlerData *handlerData, std::string path, mapInformation info);
        virtual ~Map();

        Ogre::Camera* getCamera();

        void start(GLCanvas *canvas);
        void destroy();

        void updateInput();
        void pointCamera(int xOffset, int yOffset);
        void moveCameraPosition(const Ogre::Vector3 ammount);

        void updateCursor(int x, int y);
        void handleClick(int x, int y, const int mouseButton);

        void setDefaultCameraValues(Ogre::Vector3 cameraPosition, Ogre::Vector3 cameraDirection);

        void handleTerrainEditTool(const Ogre::TerrainGroup::RayResult centreRay, const int mouseButton);
        void handleTerrainTextureTool(const Ogre::TerrainGroup::RayResult centreRay, const int mouseButton);
        void handleTerrainHeightTool(const Ogre::TerrainGroup::RayResult centreRay, const int mouseButton);

        Ogre::TerrainGroup::RayResult checkTerrainRayMouse(int x, int y);

        void saveMap(bool reSave);

        bool getMapStarted();
        mapInformation getMapInformation();

    protected:

    private:
        Ogre::Viewport *viewport;
        Ogre::Camera *camera = 0;
        Ogre::SceneManager *sceneManager;

        Ogre::Vector3 defaultCameraPosition;
        Ogre::Vector3 defaultCameraDirection;

        HandlerData *handlerData;

        Terrain *terrain;
        GLCanvas *canvas;

        bool mapStarted = false;

        float radians(float value);
        float degrees(float value);

        Ogre::SceneNode *ogreNode;
        Ogre::SceneNode *sinbadNode;

        std::string mapName;
        std::string path;
        int mapWidth;
        int mapHeight;
        int vertexCount;
        int terrainSize;
        int terrainHeight;

        float yaw = -90.0f;
        float pitch = 0.0f;
};

#endif // MAP_H
