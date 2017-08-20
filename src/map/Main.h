#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <iostream>
#include <wx/string.h>
#include <wx/arrstr.h>

class MapLoadProgressDialog;
class MainFrame;
class GLCanvas;
class Map;
class ResourceManager;
class CommandManager;

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
        void setCommandManager(CommandManager *commandManager);

        Map* getCurrentMap();
        ResourceManager* getResourceManager();
        CommandManager* getCommandManager();

        bool addResourceLocation(wxString path, bool insertAtIndex = false, int index = 0);
        void removeResourceLocation(wxString path);
        wxArrayString getResourceListItems();

        void saveProject();

        void undoAction();
        void redoAction();

        wxString getProjectDirectory();

    protected:

    private:
        GLCanvas *canvas = 0;
        Map* currentMap = 0;

        ResourceManager *resourceManager = 0;
        CommandManager *commandManager = 0;

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
