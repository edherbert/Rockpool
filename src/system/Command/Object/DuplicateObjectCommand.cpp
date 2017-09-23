#include "DuplicateObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/MeshObject.h"
#include "../../HierarchyClipboardManager.h"

DuplicateObjectCommand::DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){
    for(int i = 0; i < items.size(); i++){
        if(tree->isParentSelected(items[i])){
            continue;
        }

        ItemInformation info;
        info.id = idCount;
        info.text = tree->GetItemText(items[i]);
        info.parentId = -1;
        info.originParentItem = tree->getId(tree->GetItemParent(items[i]));

        info.originItem = tree->getId(items[i]);

        HierarchyObjectInformation *objectInfo = (HierarchyObjectInformation*)tree->GetItemData(items[i]);
        info.itemObject = objectInfo->getObject();

        info.index = tree->getItemIndex(tree->GetItemParent(items[i]), items[i]);

        itemInfo.push_back(info);
        idCount++;

        searchItem(items[i], info.id);
    }
}

DuplicateObjectCommand::~DuplicateObjectCommand(){

}

void DuplicateObjectCommand::performAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        int targetId;
        //Determine the id
        if(itemInfo[i].parentId == -1){
            //If parentId == -1 then that means that the item is a base item.
            targetId = -1;
        }else{
            targetId = itemInfo[itemInfo[i].parentId].newItem;
        }

        wxTreeItemId targetItem;
        if(targetId == -1){
            //This means that the item is a base item, so check if it should be attached to the root, or to an item.
            if(itemInfo[i].originParentItem == -1){
                targetItem = tree->GetRootItem();
            }else{
                targetItem = tree->getItem(itemInfo[i].originParentItem);
            }
        }else{
            //If none of that applies, then just get the id of the parent item.
            targetItem = tree->getItem(targetId);
        }

        wxTreeItemId newItem;
        //If it's a base item then insert needs to be run instead so that the index can be applied.
        if(itemInfo[i].parentId == -1){
            newItem = tree->InsertItem(targetItem, itemInfo[i].index, itemInfo[i].text);
        }else{
            newItem = tree->AppendItem(targetItem, itemInfo[i].text);
        }

        if(!ran){
            itemInfo[i].newItem = tree->addItem(newItem);


            //Get the object of the item to duplicate, then copy it.
            HierarchyObjectInformation *duplicateItemInfo = (HierarchyObjectInformation*)tree->GetItemData(tree->getItem(itemInfo[i].originItem));
            Object *copiedObject;

            //Check what type the item is before creating it.
            //copiedObject = duplicateObject(itemInfo[i].itemObject);
            copiedObject = tree->getClipboardManager()->copyObject(itemInfo[i].itemObject);

            //Get the parent of the duplicated item, then add the new item as a child.
            HierarchyObjectInformation *parentItemInfo = (HierarchyObjectInformation*)tree->GetItemData(targetItem);
            parentItemInfo->getObject()->addChild(copiedObject);

            //Give the object pointer to the new item
            HierarchyObjectInformation *objectInfo = new HierarchyObjectInformation(copiedObject);
            tree->SetItemData(newItem, objectInfo);

            //Copy the new mesh into the item, so that it can be referenced later
            itemInfo[i].itemObject = copiedObject;
        }else{
            //If the item is a base item, then re-append it to it's parent item.
            if(itemInfo[i].parentId == -1){
                HierarchyObjectInformation *parentItemInfo = (HierarchyObjectInformation*)tree->GetItemData(targetItem);
                parentItemInfo->getObject()->addChild(itemInfo[i].itemObject);
            }

            //Give the new item the id of the object.
            //It doesn't need to be re-copied if this is the second time the function is run.
            HierarchyObjectInformation *objectInfo = new HierarchyObjectInformation(itemInfo[i].itemObject);
            tree->SetItemData(newItem, objectInfo);

            tree->setItem(itemInfo[i].newItem, newItem);
        }
    }
    ran = true;
    tree->updateSelection();
}

void DuplicateObjectCommand::performAntiAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            itemInfo[i].itemObject->removeFromParent();

            tree->Delete(tree->getItem(itemInfo[i].newItem));
            tree->setItem(itemInfo[i].newItem, 0);
        }
    }
    tree->updateSelection();
}
