#include "ObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/MeshObject.h"

ObjectCommand::ObjectCommand(HierarchyTree *tree){
    this->tree = tree;

    this->type = objectCommand;
}

ObjectCommand::~ObjectCommand(){

}

void ObjectCommand::searchItem(wxTreeItemId item, int parentId){
    if(tree->ItemHasChildren(item)){
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = tree->GetFirstChild(item, cookie);
        while(ch.IsOk()){

            ItemInformation info;
            info.id = idCount;
            info.text = tree->GetItemText(ch);
            info.parentId = parentId;

            info.originItem = tree->getId(ch);

            HierarchyObjectInformation *objectInfo = (HierarchyObjectInformation*)tree->GetItemData(ch);
            info.itemObject = objectInfo->getObject();

            itemInfo.push_back(info);
            idCount++;
            searchItem(ch, info.id);

            ch = tree->GetNextChild(item, cookie);
        }
    }
}

void ObjectCommand::update(int x, int y){

}
