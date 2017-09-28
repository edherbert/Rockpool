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
    Ogre::Vector3 calcPosition = Ogre::Vector3(0, 0, 0);

    if(currentSelection.size() <= 0){
        //If for some reason there is no selection then set the selection position to 0
        selectionCentrePosition = calcPosition;
        return;
    }else if(currentSelection.size() == 1){
        //If there is only one selection then don't bother trying to find the mean.
        selectionCentrePosition = currentSelection[0]->getPosition();
        return;
    }

    for(int i = 0; i < currentSelection.size(); i++){
        calcPosition += currentSelection[i]->getPosition();
    }
    //Find the mean of the items
    calcPosition /= currentSelection.size();

    selectionCentrePosition = calcPosition;

    std::cout << selectionCentrePosition << std::endl;
}

Ogre::Vector3 SelectionManager::getSelectionCentrePosition(){
    return selectionCentrePosition;
}

void SelectionManager::setSelectionPosition(const Ogre::Vector3 &position){
    currentSelection[0]->setPosition(position);

    calculateSelectionCentrePosition();
}
