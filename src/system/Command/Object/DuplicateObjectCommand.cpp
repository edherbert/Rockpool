#include "DuplicateObjectCommand.h"

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
            //This means that the item is a base item, so check if it should be attached to the root, or to an itme.
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

        //Finally, determine if the item should be added or set.
        if(!ran){
            itemInfo[i].newItem = tree->addItem(newItem);
        }else{
            tree->setItem(itemInfo[i].newItem, newItem);
        }
    }
    ran = true;
}

void DuplicateObjectCommand::performAntiAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].newItem));
            tree->setItem(itemInfo[i].newItem, 0);
        }
    }
}
