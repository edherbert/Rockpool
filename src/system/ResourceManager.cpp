#include "ResourceManager.h"

#include <wx/dir.h>

ResourceManager::ResourceManager(Main *main){
    this->main = main;
}

ResourceManager::~ResourceManager(){

}

void ResourceManager::checkResourceLocations(){
    std::cout << "---Checking Resource Locations---" << std::endl;
    wxArrayString resourceLocations = main->getResourceListItems();

    locations.clear();
    if(resourceLocations.size() == 0){
        std::cout << "There are no resource locations to check." << std::endl;
        return;
    }

    for(wxString i : resourceLocations){
        wxString path = main->getProjectDirectory() + "/" + i;
        wxDir dir(path);
        if(!dir.IsOpened())return;

        resourceLocation *location = new resourceLocation;
        location->path = i;

        wxString filename;
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while(cont){
            location->resources.push_back(filename);
            cont = dir.GetNext(&filename);
        }
        locations.push_back(location);
    }

    std::cout << "Done Checking Resource Locations." << std::endl;
}

std::vector<resourceLocation*> ResourceManager::getResources(){
    return locations;
}
