#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <wx/wx.h>
#include <wx/dir.h>

#include "../ui/GLCanvas.h"
#include "Map.h"
#include "../ui/MapLoadProgressDialog.h"
#include <wx/file.h>

#include "../util/tinyxml2.h"

#include <vector>

class MapLoadProgressDialog;
class MainFrame;
class GLCanvas;
class Map;

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
        void createMap(MainFrame *frame, wxString path, wxString mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);

        void setCanvas(GLCanvas *canvas);

        Map* getCurrentMap();

        void addResourceLocation(wxString path, bool insertAtIndex = false, int index = 0);
        void removeResourceLocation(wxString path);
        wxArrayString getResourceListItems();

        wxString getProjectDirectory();

    protected:

    private:
        GLCanvas *canvas;
        Map* currentMap;

        std::vector<wxString> resourceLocationPaths;

        wxString projectDirectory;

        void showLoadFailedPopup();
        void showCreateFailedPopup();

        MapLoadProgressDialog *loadDialog;

        void createProjectFile(std::string filePath, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);
};

#endif // MAIN_H
