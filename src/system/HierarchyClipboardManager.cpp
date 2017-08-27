#include "HierarchyClipboardManager.h"

#include "../ui/Hierarchy/HierarchyTree.h"
#include "../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../map/Object/Object.h"
#include "../map/Object/MeshObject.h"

HierarchyClipboardManager::HierarchyClipboardManager(HierarchyTree *tree){
    this->tree = tree;
}

HierarchyClipboardManager::~HierarchyClipboardManager(){

}

void HierarchyClipboardManager::copyItems(const wxArrayTreeItemIds &items){
    clearClipboard();

    for(int i = 0; i < items.size(); i++){
        if(tree->isParentSelected(items[i])){
            continue;
        }

        copyInfo info;
        info.id = idCount;
        info.text = tree->GetItemText(items[i]);
        info.parentId = -1;

        HierarchyObjectInformation *originInfo = (HierarchyObjectInformation*)tree->GetItemData(items[i]);
        info.object = copyObject(originInfo->getObject());

        itemInfo.push_back(info);
        idCount++;
        searchItem(items[i], info.id);
    }
}

void HierarchyClipboardManager::clearClipboard(){
    for(int i = 0; i < itemInfo.size(); i++){
        delete itemInfo[i].object;
    }
    itemInfo.clear();
    idCount = 0;
}

Object* HierarchyClipboardManager::copyObject(Object *object){
    Object *copiedObject;

    if(object->getType() == ObjectTypeMesh){
        MeshObject *meshObject = new MeshObject((MeshObject*)object);
        copiedObject = (Object*)meshObject;
    }else if(object->getType() == ObjectTypeObject){
        copiedObject = new Object(object);
    }

    return copiedObject;
}

void HierarchyClipboardManager::searchItem(wxTreeItemId item, int parentId){
    if(tree->ItemHasChildren(item)){
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = tree->GetFirstChild(item, cookie);
        while(ch.IsOk()){
            copyInfo info;
            info.id = idCount;
            info.text = tree->GetItemText(ch);
            info.parentId = parentId;

            HierarchyObjectInformation *originInfo = (HierarchyObjectInformation*)tree->GetItemData(ch);
            info.object = copyObject(originInfo->getObject());

            itemInfo.push_back(info);
            idCount++;
            searchItem(ch, info.id);

            ch = tree->GetNextChild(item, cookie);
        }
    }
}

bool HierarchyClipboardManager::containsItems(){
    return itemInfo.size() > 0;
}

int HierarchyClipboardManager::getItemInfoSize(){
    return itemInfo.size();
}

const copyInfo& HierarchyClipboardManager::getCopyInfoItem(int index){
    return itemInfo[index];
}

