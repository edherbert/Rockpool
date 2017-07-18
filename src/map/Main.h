#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <wx/wx.h>
#include <wx/dir.h>

#include "../ui/GLCanvas.h"
#include "Map.h"
#include "../ui/Dialogs/MapLoadProgressDialog.h"
#include <wx/file.h>
#include "../system/ResourceManager.h"

#include "../util/tinyxml2.h"

#include <vector>

class MapLoadProgressDialog;
class MainFrame;
class GLCanvas;
class Map;
class ResourceManager;

struct mapInformation{
    std::string mapName;
    int mapWidth;
    int mapHeight;
    int vertexCount;
    int terrainSize;
    int terrainHeight;
};

class Main
{
    public:
        Main();
        virtual ~Main();

        void loadMap(MainFrame *frame, wxString filePath, wxString directoryPath);
        void createMap(MainFrame *frame, wxString path, mapInformation info);

        void setCanvas(GLCanvas *canvas);
        void setResourceManager(ResourceManager *resourceManager);

        Map* getCurrentMap();
        ResourceManager* getResourceManager();

        bool addResourceLocation(wxString path, bool insertAtIndex = false, int index = 0);
        void removeResourceLocation(wxString path);
        wxArrayString getResourceListItems();

        void saveProject();

        wxString getProjectDirectory();

    protected:

    private:
        GLCanvas *canvas;
        Map* currentMap;

        ResourceManager *resourceManager;

        std::vector<wxString> resourceLocationPaths;

        wxString projectDirectory;
        wxString filePath;
        wxString requiredDirectories[2] = {"terrainDat", "terrainInfo"};

        void showLoadFailedPopup();
        void showCreateFailedPopup();

        MapLoadProgressDialog *loadDialog;

        void createProjectFile(std::string filePath, mapInformation info);
};

#endif // MAIN_H
