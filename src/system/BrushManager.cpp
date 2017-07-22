#include "BrushManager.h"

BrushManager::BrushManager(Main *main){

}

BrushManager::~BrushManager(){

}

void BrushManager::getCurrentBrushData(){
    int width = 10;
    int height = 10;
    float values[width * height];
    for(int i = 0; i < width * height; i++){
        values[i] = i;
    }

//    return values;
}
