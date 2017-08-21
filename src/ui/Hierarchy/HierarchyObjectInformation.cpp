#include "HierarchyObjectInformation.h"

//#include "../../map/Object/Object.h"

HierarchyObjectInformation::HierarchyObjectInformation(Object *object){
    this->object = object;
}

HierarchyObjectInformation::~HierarchyObjectInformation(){

}

Object* HierarchyObjectInformation::getObject(){
    return object;
}
