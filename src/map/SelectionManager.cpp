#include "SelectionManager.h"

#include "Object/Object.h"
#include "../ui/Hierarchy/ObjectHierarchy.h"
#include "../ui/Hierarchy/HierarchyTree.h"
#include "../ui/Inspector/ObjectInspector.h"
#include "../system/Command/Object/PositionObjectCommand.h"
#include "../system/Command/Object/ScaleObjectCommand.h"

#include "../ui/MainFrame.h"
#include "../ui/Hierarchy/ObjectHierarchy.h"
#include "../map/Main.h"
#include "../system/Command/CommandManager.h"

SelectionManager::SelectionManager(Map *map) : map(map){

}

SelectionManager::~SelectionManager(){

}

void SelectionManager::updateCurrentSelection(){
    currentSelection = map->getObjectHierarchy()->getTree()->getSelectedObjects();
    calculateSelectionCentrePosition();

    map->getObjectInspector()->updateComponents();
}

const std::vector<Object*>& SelectionManager::getSelectionObjects(){
    return currentSelection;
}

Object* SelectionManager::getFirstObject(){
    return currentSelection[0];
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
}

Ogre::Vector3 SelectionManager::getSelectionCentrePosition(){
    return selectionCentrePosition;
}

void SelectionManager::setSelectionPosition(Ogre::Real position, ObjectAxis axis){
    PositionObjectCommand *positionCommand = new PositionObjectCommand(this, map->getObjectHierarchy()->getTree(), position, axis);
    positionCommand->performAction();

    map->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(positionCommand);
}

void SelectionManager::setSelectionScale(Ogre::Real scale, ObjectAxis axis){
    ScaleObjectCommand *scaleCommand = new ScaleObjectCommand(this, map->getObjectHierarchy()->getTree(), scale, axis);
    scaleCommand->performAction();

    map->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(scaleCommand);
}

std::array<bool, 3> SelectionManager::getPositionDifference(){
    std::array<bool, 3> returns;
    for(int i = 0; i < 3; i++){
        bool same = false;
        for(int y = 0; y < currentSelection.size(); y++){
            Ogre::Real yPos = currentSelection[y]->getPosition()[i];
            for(int x  = 0; x < currentSelection.size(); x++){
                if(x == y) continue;
                if(yPos != currentSelection[x]->getPosition()[i]){
                    same = true;
                    break;
                }
            }
            if(same)break;
        }
        returns[i] = same;
    }

    return returns;
}

std::array<bool, 3> SelectionManager::getScaleDifference(){
    std::array<bool, 3> returns;
    for(int i = 0; i < 3; i++){
        bool same = false;
        for(int y = 0; y < currentSelection.size(); y++){
            Ogre::Real yScale = currentSelection[y]->getScale()[i];
            for(int x = 0; x < currentSelection.size(); x++){
                if(x == y) continue;
                if(yScale != currentSelection[x]->getScale()[i]){
                    same = true;
                    break;
                }
            }
            if(same) break;
        }
        returns[i] = same;
    }

    return returns;
}
