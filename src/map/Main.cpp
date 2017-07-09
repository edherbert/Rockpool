#include "Main.h"

Main::Main(){

}

Main::~Main(){

}

void Main::loadMap(MainFrame *frame, wxString filePath, wxString directoryPath){
    if(!canvas) return;
    //loadDialog = new MapLoadProgressDialog(canvas->GetParent());
    //loadDialog->setText("Creating Project");
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(filePath);

    tinyxml2::XMLNode *root = xmlDoc.FirstChild();
    tinyxml2::XMLElement *header = root->FirstChildElement("Header");
    tinyxml2::XMLElement *resources = root->FirstChildElement("Resources");

    tinyxml2::XMLElement *mapSettings = header->FirstChildElement("mapSettings");
    std::string mapName = mapSettings->Attribute("mapName");
    int mapWidth = mapSettings->IntAttribute("mapWidth");
    int mapHeight = mapSettings->IntAttribute("mapHeight");
    int vertexCount = mapSettings->IntAttribute("vertexCount");
    int terrainSize = mapSettings->IntAttribute("terrainSize");
    int terrainHeight = mapSettings->IntAttribute("terrainHeight");

    std::cout << filePath << std::endl;
    std::cout << directoryPath << std::endl;

    for(tinyxml2::XMLElement *e = resources->FirstChildElement("location"); e != NULL; e = e->NextSiblingElement("location")){
        Ogre::Root::getSingleton().addResourceLocation(Ogre::String(directoryPath + "/" + e->Attribute("path")), "FileSystem");
    }

    currentMap = new Map(frame->getHandlerData(), (std::string)directoryPath, mapName, mapWidth, mapHeight, vertexCount, terrainSize, terrainHeight);
    canvas->setMap(currentMap);
    //loadDialog->addValue(10);
    //loadDialog->setText("Generating Terrain");
}

void Main::createMap(MainFrame *frame, wxString directoryPath, wxString mapName, int mapWidth, int mapHeight, int vertexCount, int terrainSize, int terrainHeight){
    wxString root = directoryPath + "/" + mapName;
    if(wxMkdir(root)){
        for(int i = 0; i < sizeof(defaultResourceLocations) / sizeof(*defaultResourceLocations); i++){
            wxMkdir(root + "/" + defaultResourceLocations[i]);
        }

        std::string filePath = (std::string)(root + "/" + mapName + ".rockpool");
        createProjectFile(filePath, (std::string)mapName, mapWidth, mapHeight, vertexCount, terrainSize, terrainHeight);

        std::cout << directoryPath << std::endl;

        loadMap(frame, (wxString)filePath, root);
    }
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

    for(int i = 0; i < sizeof(defaultResourceLocations) / sizeof(*defaultResourceLocations); i++){
        tinyxml2::XMLElement *location = doc.NewElement("location");
        location->SetAttribute("path", defaultResourceLocations[i].c_str());
        resources->InsertFirstChild(location);
    }

    rockpoolProject->InsertFirstChild(header);
    rockpoolProject->InsertEndChild(resources);
    doc.InsertFirstChild(rockpoolProject);
    doc.SaveFile(filePath.c_str());
}

void Main::setCanvas(GLCanvas *canvas){
    this->canvas = canvas;
}

Map* Main::getCurrentMap(){
    return currentMap;
}
