#ifndef MAP_H
#define MAP_H

#include <OGRE/Ogre.h>
#include <Terrain/OgreTerrainGroup.h>

class GLCanvas;
class ToolPreferencesHandler;
class TerrainInfoHandler;
class TerrainCommand;
class Terrain;
class Object;

struct HandlerData;
struct mapInformation;

struct terrainTextureCommandInformation;
struct terrainCommandInformation;
struct terrainSquareInformation;
struct terrainBrushInformation;

class Map
{
    public:
        Map(HandlerData *handlerData, std::string path, mapInformation info);
        virtual ~Map();

        Ogre::Camera* getCamera();
        Ogre::SceneManager* getSceneManager();

        void start(GLCanvas *canvas);
        void destroy();

        void updateInput();
        void pointCamera(int xOffset, int yOffset);
        void moveCameraPosition(const Ogre::Vector3 ammount);

        void updateCursor(int x, int y);
        void handleClick(int x, int y, const int mouseButton);

        void setDefaultCameraValues(Ogre::Vector3 cameraPosition, Ogre::Vector3 cameraDirection);

        void handleTerrainTool(const Ogre::TerrainGroup::RayResult centreRay, const int mouseButton, const int toolId);
        terrainSquareInformation genSquareInfo(Ogre::Terrain *terr, int x, int y, int z, int brushSize, bool textureTool = false);
        Ogre::TerrainGroup::RayResult checkTerrainRayMouse(int x, int y);

        void saveMap(bool reSave);

        void addObject(Object *object);

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
        TerrainCommand *currentTerrainCommand = 0;

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
