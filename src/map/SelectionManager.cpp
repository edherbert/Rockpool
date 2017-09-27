#include "SelectionManager.h"

#include "Object/Object.h"
#include "../ui/Hierarchy/ObjectHierarchy.h"
#include "../ui/Hierarchy/HierarchyTree.h"
#include "../ui/Inspector/ObjectInspector.h"

SelectionManager::SelectionManager(Map *map) : map(map){

}

SelectionManager::~SelectionManager(){

}

void SelectionManager::updateCurrentSelection(){
    currentSelection = map->getObjectHierarchy()->getTree()->getSelectedObjects();
    calculateSelectionCentrePosition();

    map->getObjectInspector()->updateComponents();
}

void SelectionManager::calculateSelectionCentrePosition(){
    Ogre::Vector3 calcPosition;

    if(currentSelection.size() <= 0){
        selectionCentrePosition = calcPosition;
        return;
    }else if(currentSelection.size() == 1){
        selectionCentrePosition = currentSelection[0]->getPosition();
        return;
    }

    for(int i = 0; i < currentSelection.size(); i++){
        calcPosition += currentSelection[i]->getPosition();
    }
    //Find the mean of the items
    calcPosition /= currentSelection.size();

    selectionCentrePosition = calcPosition;
}

Ogre::Vector3 SelectionManager::getSelectionCentrePosition(){
    return selectionCentrePosition;
}

void SelectionManager::setSelectionPosition(const Ogre::Vector3 &position){
    //For now set it to the exact location, later on this will have to be done relative to the current position.
    currentSelection[0]->setPosition(position);
}
