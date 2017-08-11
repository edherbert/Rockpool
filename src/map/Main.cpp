#include "Main.h"

Main::Main(){

}

Main::~Main(){

}

void Main::loadMap(MainFrame *frame, wxString filePath, wxString directoryPath){
    if(!canvas) return;
    bool success = true;

    //Check if this directory can be written to
    //Theres no point in opening it if it can't be written to.
    if(!wxFileName::IsDirWritable(directoryPath) && wxFileName::IsDirReadable(directoryPath)){
        wxMessageDialog dialog(canvas, wxT("Rockpool was unable to open the file in this directory as it is either un-readable or un-writable."));
        dialog.ShowModal();
        return;
    }
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
    Ogre::Vector3 cameraPosition(0, 100, 200);
    Ogre::Vector3 cameraDirection;

    if(header){
        tinyxml2::XMLElement *mapSettings = header->FirstChildElement("mapSettings");
        info.mapName = mapSettings->Attribute("mapName");
        info.mapWidth = mapSettings->IntAttribute("mapWidth");
        info.mapHeight = mapSettings->IntAttribute("mapHeight");
        info.vertexCount = mapSettings->IntAttribute("vertexCount");
        info.terrainSize = mapSettings->IntAttribute("terrainSize");
        info.terrainHeight = mapSettings->IntAttribute("terrainHeight");


        tinyxml2::XMLElement *cameraPositionElement = header->FirstChildElement("cameraPosition");

        if(cameraPositionElement){
            cameraPosition.x = cameraPositionElement->FloatAttribute("x");
            cameraPosition.y = cameraPositionElement->FloatAttribute("y");
            cameraPosition.z = cameraPositionElement->FloatAttribute("z");

            cameraDirection.x = cameraPositionElement->FloatAttribute("dirX");
            cameraDirection.y = cameraPositionElement->FloatAttribute("dirY");
            cameraDirection.z = cameraPositionElement->FloatAttribute("dirZ");
        }
    }else success = false;

    this->projectDirectory = directoryPath;
    this->filePath = filePath;

    if(resources){
        for(tinyxml2::XMLElement *e = resources->FirstChildElement("location"); e != NULL; e = e->NextSiblingElement("location")){
            if(e){
                addResourceLocation(directoryPath + "/" + e->Attribute("path"));
            }else{
                success = false;
            }
        }
    }else success = false;

    if(resourceManager){
        resourceManager->checkResourceLocations();
        frame->getResourceBrowser()->updateTiles();
        frame->getResourceBrowser()->layoutTiles();
    }

    if(!success){
        showLoadFailedPopup();
        return;
    }

    //These are required directories, and have nothing to do with the directories that the user can add
    //They are added like this so that they're not pushed to the resource location list that the user can see.
    for(wxString i : requiredDirectories){
        Ogre::Root::getSingleton().addResourceLocation(Ogre::String(directoryPath + "/" + i), "FileSystem");
    }

    currentMap = new Map(frame->getHandlerData(), (std::string)directoryPath, info);
    currentMap->setDefaultCameraValues(cameraPosition, cameraDirection);
    canvas->setMap(currentMap);
    frame->getObjectHierarchy()->setMap(currentMap);
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

void Main::createMap(MainFrame *frame, wxString directoryPath, mapInformation info){
    wxString root = directoryPath + "/" + info.mapName;
    bool success = true;

    //If none of the directories can be created then show a message and return
    if(!wxMkdir(root) || !wxMkdir(root + "/terrainDat") || !wxMkdir(root + "/terrainInfo")){
        showCreateFailedPopup();
        return;
    }

    std::string filePath = (std::string)(root + "/" + info.mapName + ".rockpool");
    createProjectFile(filePath, info);

    loadMap(frame, (wxString)filePath, root);
}

void Main::createProjectFile(std::string filePath, mapInformation info){
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLNode *rockpoolProject = doc.NewElement("Rockpool_project");
    tinyxml2::XMLNode *header = doc.NewElement("Header");

    tinyxml2::XMLElement *headerMapSettings = doc.NewElement("mapSettings");
    headerMapSettings->SetAttribute("mapName", info.mapName.c_str());
    headerMapSettings->SetAttribute("mapWidth", info.mapWidth);
    headerMapSettings->SetAttribute("mapHeight", info.mapHeight);
    headerMapSettings->SetAttribute("vertexCount", info.vertexCount);
    headerMapSettings->SetAttribute("terrainSize", info.terrainSize);
    headerMapSettings->SetAttribute("terrainHeight", info.terrainHeight);
    header->InsertEndChild(headerMapSettings);

    //Set the values for the camera
    tinyxml2::XMLElement *headerCameraPosition = doc.NewElement("cameraPosition");
    Ogre::Real cameraX = 0;
    Ogre::Real cameraY = 30;
    Ogre::Real cameraZ = 0;
    Ogre::Real cameraDirectionX = 0;
    Ogre::Real cameraDirectionY = 0;
    Ogre::Real cameraDirectionZ = 0;
    //This function is called during file creation as well as saving, so check if there is a map to save camera values for
    //Otherwise, just use the default ones.
    if(currentMap && currentMap->getCamera()){
        Ogre::Vector3 position = currentMap->getCamera()->getPosition();
        cameraX = position.x;
        cameraY = position.y;
        cameraZ = position.z;
        Ogre::Vector3 direction = currentMap->getCamera()->getDirection();
        cameraDirectionX = direction.x;
        cameraDirectionY = direction.y;
        cameraDirectionZ = direction.z;
    }
    headerCameraPosition->SetAttribute("x", cameraX);
    headerCameraPosition->SetAttribute("y", cameraY);
    headerCameraPosition->SetAttribute("z", cameraZ);
    headerCameraPosition->SetAttribute("dirX", cameraDirectionX);
    headerCameraPosition->SetAttribute("dirY", cameraDirectionY);
    headerCameraPosition->SetAttribute("dirZ", cameraDirectionZ);
    header->InsertEndChild(headerCameraPosition);

    tinyxml2::XMLNode *resources = doc.NewElement("Resources");

    for(wxString i : resourceLocationPaths){
        tinyxml2::XMLElement *location = doc.NewElement("location");
        location->SetAttribute("path", ((std::string)i).c_str());
        resources->InsertFirstChild(location);
    }

    rockpoolProject->InsertFirstChild(header);
    rockpoolProject->InsertEndChild(resources);
    doc.InsertFirstChild(rockpoolProject);
    doc.SaveFile(filePath.c_str());
}

bool Main::addResourceLocation(wxString path, bool insertAtIndex, int index){
    wxFileName file(path);
    if(!file.IsDirReadable() || !file.Exists()) return false;

    //Check if the new location is one of the required locations
    for(wxString i : requiredDirectories){
        if(projectDirectory + "/" + i == path){
            if(!canvas)return false;
            wxMessageDialog dialog(canvas, wxT("That's one of the required directories.\nYou can't add it as a resource location."));
            dialog.ShowModal();
            return false;
        }
    }

    //The index is for the location editing
    wxString insertValue = path.substr(projectDirectory.size() + 1, path.size());
    if(insertAtIndex){
        resourceLocationPaths.insert(resourceLocationPaths.begin()+index, insertValue);
    }else{
        resourceLocationPaths.push_back(insertValue);
    }
    Ogre::Root::getSingleton().addResourceLocation((Ogre::String)path, "FileSystem");

    return true;
}

void Main::removeResourceLocation(wxString path){
    //There is no need to check if the path exists and all that here, just delete it.
    std::string shorter = (std::string)path.substr(projectDirectory.size() + 1, path.size());

    resourceLocationPaths.erase(std::remove(resourceLocationPaths.begin(), resourceLocationPaths.end(), shorter), resourceLocationPaths.end());
    Ogre::Root::getSingleton().removeResourceLocation((Ogre::String)path);
}

void Main::saveProject(){
    std::cout << "saving project" << std::endl;
    //Check if the project directory exists, otherwise create it.
    //This is incase the user changes the directory name or something while Rockpool is running.
    if(!wxDir::Exists(projectDirectory)){
        wxMkdir(projectDirectory);
    }
    //If the project directory can't be written to then tell the user.
    if(!wxFileName::IsDirWritable(projectDirectory)){
        std::cout << "Not writable" << std::endl;
        wxMessageDialog dialog(canvas, wxT("Rockpool was unable to save the project as the working directory is not writable."));
        dialog.ShowModal();
        return;
    }
    createProjectFile((std::string)filePath, currentMap->getMapInformation());

    bool reSave = false;
    for(wxString s : requiredDirectories){
        if(!wxDir::Exists(projectDirectory + "/" + s)){
            wxMkdir(projectDirectory + "/" + s);
            reSave = true;
        }
    }

    currentMap->saveMap(reSave);
}

void Main::setCanvas(GLCanvas *canvas){
    this->canvas = canvas;
}

void Main::setResourceManager(ResourceManager *resourceManager){
    this->resourceManager = resourceManager;
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

ResourceManager* Main::getResourceManager(){
    return resourceManager;
}

void Main::setCommandManager(CommandManager *commandManager){
    this->commandManager = commandManager;
}

void Main::undoAction(){
    if(!commandManager) return;
    commandManager->undoLastCommand();
}

void Main::redoAction(){
    if(!commandManager) return;
    commandManager->redoLastCommand();
}

CommandManager* Main::getCommandManager(){
    return commandManager;
}
