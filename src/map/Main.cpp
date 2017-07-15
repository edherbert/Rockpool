#include "Main.h"

Main::Main(){

}

Main::~Main(){

}

void Main::loadMap(MainFrame *frame, wxString filePath, wxString directoryPath){
    if(!canvas) return;
    bool success = true;
    //loadDialog = new MapLoadProgressDialog(canvas->GetParent());
    //loadDialog->setText("Creating Project");
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(filePath);

    tinyxml2::XMLNode *root = xmlDoc.FirstChild();
    if(!root){
        showLoadFailedPopup();
        return;
    }
    tinyxml2::XMLElement *header = root->FirstChildElement("Header");
    tinyxml2::XMLElement *resources = root->FirstChildElement("Resources");

    mapInformation info;

    if(header){
        tinyxml2::XMLElement *mapSettings = header->FirstChildElement("mapSettings");
        info.mapName = mapSettings->Attribute("mapName");
        info.mapWidth = mapSettings->IntAttribute("mapWidth");
        info.mapHeight = mapSettings->IntAttribute("mapHeight");
        info.vertexCount = mapSettings->IntAttribute("vertexCount");
        info.terrainSize = mapSettings->IntAttribute("terrainSize");
        info.terrainHeight = mapSettings->IntAttribute("terrainHeight");
    }else success = false;

    this->projectDirectory = directoryPath;

    if(resources){
        for(tinyxml2::XMLElement *e = resources->FirstChildElement("location"); e != NULL; e = e->NextSiblingElement("location")){
            if(e){
                addResourceLocation(directoryPath + "/" + e->Attribute("path"));
                std::cout << directoryPath + "/" + e->Attribute("path") << std::endl;
            }else{
                success = false;
            }
        }
    }else success = false;

    if(!success){
        showLoadFailedPopup();
        return;
    }

    Ogre::Root::getSingleton().addResourceLocation(Ogre::String(directoryPath + "/TerrainDat"), "FileSystem");
    Ogre::Root::getSingleton().addResourceLocation(Ogre::String(directoryPath + "/TerrainInfo"), "FileSystem");

    std::cout << filePath << std::endl;
    std::cout << directoryPath << std::endl;

    currentMap = new Map(frame->getHandlerData(), (std::string)directoryPath, info.mapName, info.mapWidth, info.mapHeight, info.vertexCount, info.terrainSize, info.terrainHeight);
    canvas->setMap(currentMap);
    //loadDialog->addValue(10);
    //loadDialog->setText("Generating Terrain");
}

void Main::showLoadFailedPopup(){
    if(!canvas)return;
    //Attach it to the canvas because it has to be attached to something
    wxMessageDialog dialog(canvas, wxT("Rockpool was unable to open this file!\nIt is either not a Rockpool file or it has been corrupted in some way."));
    dialog.ShowModal();
}

void Main::showCreateFailedPopup(){
    if(!canvas)return;
    wxMessageDialog dialog(canvas, wxT("Rockpool was unable to create a project directory in this location!\nThis could be because you do not have write permissions, or the directory does not exist."));
    dialog.ShowModal();
}

void Main::createMap(MainFrame *frame, wxString directoryPath, wxString mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight){
    wxString root = directoryPath + "/" + mapName;
    bool success = true;

    //If none of the directories can be created then show a message and return
    if(!wxMkdir(root) || !wxMkdir(root + "/terrainDat") || !wxMkdir(root + "/terrainInfo")){
        showCreateFailedPopup();
        return;
    }

    std::string filePath = (std::string)(root + "/" + mapName + ".rockpool");
    createProjectFile(filePath, (std::string)mapName, mapWidth, mapHeight, vertexCount, terrainSize, terrainHeight);

    loadMap(frame, (wxString)filePath, root);
}

void Main::createProjectFile(std::string filePath, std::string mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight){
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLNode *rockpoolProject = doc.NewElement("Rockpool_project");
    tinyxml2::XMLNode *header = doc.NewElement("Header");

    tinyxml2::XMLElement *headerMapSettings = doc.NewElement("mapSettings");
    headerMapSettings->SetAttribute("mapName", mapName.c_str());
    headerMapSettings->SetAttribute("mapWidth", mapWidth);
    headerMapSettings->SetAttribute("mapHeight", mapHeight);
    headerMapSettings->SetAttribute("vertexCount", vertexCount);
    headerMapSettings->SetAttribute("terrainSize", terrainSize);
    headerMapSettings->SetAttribute("terrainHeight", terrainHeight);
    header->InsertEndChild(headerMapSettings);

    tinyxml2::XMLNode *resources = doc.NewElement("Resources");

    /*for(int i = 0; i < 3; i++){
        tinyxml2::XMLElement *location = doc.NewElement("location");
        location->SetAttribute("path", "hello");
        resources->InsertFirstChild(location);
    }*/

    rockpoolProject->InsertFirstChild(header);
    rockpoolProject->InsertEndChild(resources);
    doc.InsertFirstChild(rockpoolProject);
    doc.SaveFile(filePath.c_str());
}

void Main::addResourceLocation(wxString path, bool insertAtIndex, int index){
    wxFileName file(path);
    if(file.IsDirReadable() && file.Exists()){
        //The index is for the location editing
        wxString insertValue = path.substr(projectDirectory.size() + 1, path.size());
        if(insertAtIndex){
            resourceLocationPaths.insert(resourceLocationPaths.begin()+index, insertValue);
        }else{
            resourceLocationPaths.push_back(insertValue);
        }
        Ogre::Root::getSingleton().addResourceLocation((Ogre::String)path, "FileSystem");
    }
}

void Main::removeResourceLocation(wxString path){
    //There is no need to check if the path exists and all that here, just delete it.
    std::string shorter = (std::string)path.substr(projectDirectory.size() + 1, path.size());

    resourceLocationPaths.erase(std::remove(resourceLocationPaths.begin(), resourceLocationPaths.end(), shorter), resourceLocationPaths.end());
    Ogre::Root::getSingleton().removeResourceLocation((Ogre::String)path);
}

void Main::setCanvas(GLCanvas *canvas){
    this->canvas = canvas;
}

Map* Main::getCurrentMap(){
    return currentMap;
}

wxString Main::getProjectDirectory(){
    return projectDirectory;
}

wxArrayString Main::getResourceListItems(){
    wxArrayString items;
    for(wxString i : resourceLocationPaths){
        items.Add(i);
    }
    return items;
}
