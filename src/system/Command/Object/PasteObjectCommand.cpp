#include "PasteObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../HierarchyClipboardManager.h"

PasteObjectCommand::PasteObjectCommand(HierarchyTree *tree, HierarchyClipboardManager *clipboardManager, int destinationId) : ObjectCommand(tree){
    this->clipboardManager = clipboardManager;
    this->destinationId = destinationId;

    for(int i = 0; i < clipboardManager->getItemInfoSize(); i++){
        const copyInfo &copiedInformation = clipboardManager->getCopyInfoItem(i);

        ItemInformation info;
        info.text = copiedInformation.text;
        info.id = copiedInformation.id;
        info.parentId = copiedInformation.parentId;

        info.itemObject = clipboardManager->copyObject(copiedInformation.object);

        itemInfo.push_back(info);
    }
}

PasteObjectCommand::~PasteObjectCommand(){

}

void PasteObjectCommand::performAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        wxTreeItemId targetItem;
        if(itemInfo[i].parentId == -1){
            if(destinationId == -1){
                targetItem = tree->GetRootItem();
            }else{
                targetItem = tree->getItem(destinationId);
            }
        }else{
            targetItem = tree->getItem(itemInfo[itemInfo[i].parentId].newItem);
        }

        HierarchyObjectInformation *parentInfo = (HierarchyObjectInformation*)tree->GetItemData(targetItem);
        parentInfo->getObject()->addChild(itemInfo[i].itemObject);

        HierarchyObjectInformation *objectInfo = new HierarchyObjectInformation(itemInfo[i].itemObject);

        wxTreeItemId newItem = tree->AppendItem(targetItem, itemInfo[i].text, -1, -1, objectInfo);

        if(!ran){
            itemInfo[i].newItem = tree->addItem(newItem);
        }else{
            tree->setItem(itemInfo[i].newItem, newItem);
        }

    }
    ran = true;
}

void PasteObjectCommand::performAntiAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            HierarchyObjectInformation *objectInfo = (HierarchyObjectInformation*)tree->GetItemData(tree->getItem(itemInfo[i].newItem));
            objectInfo->getObject()->removeFromParent();

            tree->Delete(tree->getItem(itemInfo[i].newItem));
        }
    }
}
