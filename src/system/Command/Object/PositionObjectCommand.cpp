#include "PositionObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

#include "../../../map/SelectionManager.h"
#include "../../../ui/Inspector/ObjectInspector.h"

PositionObjectCommand::PositionObjectCommand(SelectionManager *selectionManager, HierarchyTree *hierarchyTree, Ogre::Real position, ObjectAxis axis) : ObjectCommand(hierarchyTree),
    position(position),
    axis(axis){

    std::vector<Object*> selectedObjects = selectionManager->getSelectionObjects();
    for(int i = 0; i < selectedObjects.size(); i++){
        ObjectValues vals;
        vals.object = selectedObjects[i];
        vals.originPosition = vals.object->getPosition();

        objectVals.push_back(vals);
    }
}

PositionObjectCommand::~PositionObjectCommand(){

}

void PositionObjectCommand::performAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setAxisPosition(axis, position);
    }
    tree->getMap()->getSelectionManager()->updateCurrentSelection();
}

void PositionObjectCommand::performAntiAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition);
    }
    tree->getMap()->getSelectionManager()->updateCurrentSelection();
}
