#include "ScaleObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

#include "../../../map/SelectionManager.h"
#include "../../../ui/Inspector/ObjectInspector.h"

ScaleObjectCommand::ScaleObjectCommand(SelectionManager *selectionManager, HierarchyTree *hierarchyTree, Ogre::Real scale, ObjectAxis axis) : ObjectCommand(hierarchyTree),
    scale(scale),
    axis(axis){

    std::vector<Object*> selectedObjects = selectionManager->getSelectionObjects();
    for(int i = 0; i < selectedObjects.size(); i++){
        ObjectScaleValues vals;
        vals.object = selectedObjects[i];
        vals.originScale = vals.object->getScale();

        objectVals.push_back(vals);
    }

}

ScaleObjectCommand::~ScaleObjectCommand(){

}

void ScaleObjectCommand::performAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setAxisScale(axis, scale);
    }
    tree->getMap()->getSelectionManager()->updateCurrentSelection();
}

void ScaleObjectCommand::performAntiAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setScale(objectVals[i].originScale);
    }
    tree->getMap()->getSelectionManager()->updateCurrentSelection();
}
