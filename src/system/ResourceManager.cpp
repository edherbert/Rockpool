#include "ResourceManager.h"

ResourceManager::ResourceManager(Main *main){
    this->main = main;
}

ResourceManager::~ResourceManager(){

}

void ResourceManager::checkResourceLocations(){
    wxLongLong startTime = wxGetLocalTimeMillis();
    std::cout << "---CHECKING RESOURCE LOCATIONS---" << std::endl;
    wxArrayString resourceLocations = main->getResourceListItems();

    if(resourceLocations.size() == 0){
        std::cout << "There are no resource locations to check." << std::endl;
        return;
    }

    for(wxString i : resourceLocations){
        wxString path = main->getProjectDirectory() + "/" + i;
        //wxFile dir(path);
        wxDir dir(path);
        if(!dir.IsOpened())return;

        //Check if this resource location is already in the locations list
        bool locationExistsAlready = false;
        resourceLocation *location;
        /*for(resourceLocation *r : locations){
            if(r->path == i){
                std::cout << "LOCATION EXISTS" << std::endl;
                locationExistsAlready = true;
                location = r;
                break;
            }
        }*/
        for(int r = 0; r < locations.size(); r++){
            if(locations.at(r)->path == i){
                std::cout << "LOCATION EXISTS" << std::endl;
                locationExistsAlready = true;
                location = locations.at(r);
                break;
            }
        }
        if(!locationExistsAlready){
            std::cout << "LOCATION DOESNT EXISTS" << std::endl;
            location = new resourceLocation;
            location->path = i;
        }

        std::cout << location << std::endl;

        //It could be something to do with this bit here.
        //Maybe once the resources are pushed the old ones are removed, because of garbage collection.
        wxString filename;
        bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
        while(cont){
            location->resources.push_back(filename);
            cont = dir.GetNext(&filename);
        }

        if(!locationExistsAlready){
            locations.push_back(location);
        }
    }

    wxLongLong endTime = wxGetLocalTimeMillis();

    for(resourceLocation *r : locations){
        for(wxString s : r->resources){
            //std::cout << s << std::endl;
        }
    }

    std::cout << "Time taken: " << endTime - startTime << " Milliseconds" << std::endl << " " << std::endl;

}

/*
Maybe I should have a vector created when I search through the locations.
I would create a duplicate of the current string vector for this location, say called currentResources.
I would then have the list of resources that are currently in the resource location, so newResouces.

I would check through currentResources and see if new resources has that file.
If it does then remove it from both lists.
By the end of this, the files that are in new resources are new files and should be added.
The files that are in the current resources are old and have been deleted in the directory, so get rid of them.
*/
