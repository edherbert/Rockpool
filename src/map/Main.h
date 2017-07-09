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

class MapLoadProgressDialog;
class MainFrame;
class GLCanvas;
class Map;

class Main
{
    public:
        Main();
        virtual ~Main();

        void loadMap(MainFrame *frame, wxString filePath, wxString directoryPath);
        void createMap(MainFrame *frame, wxString path, wxString mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);

        void setCanvas(GLCanvas *canvas);

        Map* getCurrentMap();

    protected:

    private:
        GLCanvas *canvas;
        Map* currentMap;

        const std::string defaultResourceLocations[3] = {"Terrains", "Meshes", "Textures"};

        MapLoadProgressDialog *loadDialog;

        void createProjectFile(std::string filePath, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight);
};

#endif // MAIN_H
