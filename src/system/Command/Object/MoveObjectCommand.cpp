#include "MoveObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/Object.h"

MoveObjectCommand::MoveObjectCommand(HierarchyTree *tree) : ObjectCommand(tree){
    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    for(int i = 0; i < items.size(); i++){
        if(tree->isParentSelected(items[i])){
            continue;
        }
        HierarchyObjectInformation *info = (HierarchyObjectInformation*) tree->GetItemData(items[i]);

        ObjectValues vals;
        vals.object = info->getObject();
        vals.originPosition = vals.object->getPosition();

        objectVals.push_back(vals);
    }
}

MoveObjectCommand::~MoveObjectCommand(){

}

void MoveObjectCommand::update(int x, int y){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].object->getPosition() + Ogre::Vector3(x, y, 0));
    }
    totalX += x;
    totalY += y;
}

void MoveObjectCommand::performAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].object->getPosition() + Ogre::Vector3(totalX, totalY, 0));
    }
}

void MoveObjectCommand::performAntiAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition);
    }
}
