#include "PositionObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

#include "../../../map/SelectionManager.h"

PositionObjectCommand::PositionObjectCommand(SelectionManager *selectionManager, Ogre::Real position, ObjectAxis axis) : ObjectCommand(tree),
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
}

void PositionObjectCommand::performAntiAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition);
    }
}
