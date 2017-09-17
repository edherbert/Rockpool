#include "SkyBox.h"

SkyBox::SkyBox(){

}

SkyBox::~SkyBox(){

}

void SkyBox::setSkyBoxValue(int index, const wxString& value){
    paths[index] = value;
}

wxString SkyBox::getSkyBoxValue(int index){
    return paths[index];
}

void SkyBox::copyValuesFrom(SkyBox *skybox){
    setName(skybox->getName());
    for(int i = 0; i < 6; i++){
        setSkyBoxValue(i, skybox->getSkyBoxValue(i));
    }
}

void SkyBox::setName(const wxString& name){
    this->name = name;
}

wxString SkyBox::getName(){
    return name;
}
