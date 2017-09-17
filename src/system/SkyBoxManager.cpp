#include "SkyBoxManager.h"

#include "../map/SkyBox.h"

SkyBoxManager::SkyBoxManager(){

}

SkyBoxManager::~SkyBoxManager(){

}

void SkyBoxManager::addSkyBox(SkyBox *skybox){
    skyboxes.push_back(skybox);
}

int SkyBoxManager::getSkyBoxCount(){
    return skyboxes.size();
}

SkyBox* SkyBoxManager::getSkyBoxAt(int index){
    return skyboxes[index];
}

void SkyBoxManager::deleteSkyBoxAt(int index){
    delete skyboxes[index];
    skyboxes.erase(skyboxes.begin() + index);
}
