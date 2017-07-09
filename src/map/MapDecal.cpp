#include "MapDecal.h"

MapDecal::MapDecal(Ogre::SceneManager *sceneManager, Terrain *terrain){
    this->sceneManager = sceneManager;
    this->terrain = terrain;

    object = sceneManager->createManualObject("manual");

    object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);

    /*for(int y = 1; y < 3; y++){
        for(int x = 1; x < 3; x++){
            object->position(-x * 10, -y * 10, 0.0);
            object->position( x * 10, -y * 10, 0.0);
            object->position( x * 10,  y * 10, 0.0);
            object->position(-x * 10,  y * 10, 0.0);
        }
    }

    int sizeOfBuffer = 4;
    // define usage of vertices by refering to the indexes
    for(int i = 0; i < 3; i++){
        object->index(0 + (i * sizeOfBuffer));
        object->index(1 + (i * sizeOfBuffer));
        object->index(2 + (i * sizeOfBuffer));
        object->index(3 + (i * sizeOfBuffer));
        object->index(0 + (i * sizeOfBuffer));
    }*/

    //10 verts means 5 cubes
/*    for(int y = 0; y < 10; y++){
        for(int x = 0; x < 10; x++){
            object->position(x * 10, y * 10, 0.0);
        }
    }*/

    /*for(int y = 0; y < 10; y++){
        for(int x = 0; x < 10; x++){
            //object->position(x * 10, y * 10, 0);
            //object->position(x * 10 + 10, y * 10, 0);

            //object->position(x * 10, y * 10, 0);
            //object->position(x * 10, y * 10 + 10, 0);

            object->position(x * 10, y * 10, 0);
            object->position(x * 10 + 10, y * 10, 0);
            object->position(x * 10, y * 10 + 10, 0);
        }
    }*/



    //object->index(1);
    //object->index(5);
    //object->index(4);
    //object->index(0);
    //object->index(1);

    //object->index(1);
    //object->index(4);
    //object->index(5);
    //object->index(2);
    //object->index(1);

    //object->index(0);
    //object->index(1);
    //object->index(3);
    //object->index(4);
    //object->index(5);
    //object->index(2);

    /*
    object->index(0);
    object->index(3);

    object->index(3);
    object->index(4);

    object->index(4);
    object->index(1);

    object->index(1);
    object->index(0);

    object->index(1);
    object->index(4);

    object->index(4);
    object->index(5);

    object->index(5);
    object->index(2);

    object->index(2);
    object->index(1);
    */

    //10, 0
    //0, 0
    //30, 0
    //10, 0

    /*0, 0
    10, 0
    20, 0
    30, 0

    0, 10
    10, 10
    20, 10
    30, 10

    0, 20
    10, 20
    20, 20
    30, 20

    0, 30
    10, 30
    20, 30
    30, 30*/



    object->end();

    //Only when the radius changes does the buffer need to be re-created.
    //It would be simple to guess the number of verticies.

    sceneManager->getRootSceneNode()->attachObject(object);
}

MapDecal::~MapDecal(){

}

void MapDecal::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}


void MapDecal::setRadius(int radius){
    this->radius = radius;
}

void MapDecal::calculateGeometry(){

}
