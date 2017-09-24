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
    }

    for(int i = 0; i < currentSelection.size(); i++){
        calcPosition += currentSelection[i]->getPosition();
    }
    //Find the mean of the items
    calcPosition /= currentSelection.size();

    selectionCentrePosition = calcPosition;
}
