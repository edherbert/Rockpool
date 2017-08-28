#include "MoveObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

MoveObjectCommand::MoveObjectCommand(HierarchyTree *tree) : ObjectCommand(tree){
    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    //Go through the selection and catalogue the items to be moved.
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

void MoveObjectCommand::update(const Ogre::Vector3 &current, TargetAxis axis){
    if(axis == TargetAxisX){
        delta.x += (current - previous).x;
    }else if(axis == TargetAxisY){
        delta.y += (current - previous).y;
    }else if(axis == TargetAxisZ){
        delta.z += (current - previous).z;
    }

    std::cout << delta.z << std::endl;

    previous = current;

    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition + delta);
        //objectVals[i].object->setPosition(current);
    }

}

void MoveObjectCommand::performAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition + delta);
    }
}

void MoveObjectCommand::performAntiAction(){
    for(int i = 0; i < objectVals.size(); i++){
        objectVals[i].object->setPosition(objectVals[i].originPosition);
    }
}
