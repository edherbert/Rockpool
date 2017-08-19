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

        itemInfo.push_back(info);
        idCount++;

        searchItem(items[i], info.id);
    }
}

void DuplicateObjectCommand::searchItem(wxTreeItemId item, int parentId){
    if(tree->ItemHasChildren(item)){
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = tree->GetFirstChild(item, cookie);
        while(ch.IsOk()){

            ItemInformation info;
            info.id = idCount;
            info.text = tree->GetItemText(ch);
            info.parentId = parentId;

            info.originItem = tree->getId(ch);

            itemInfo.push_back(info);
            idCount++;
            searchItem(ch, info.id);

            ch = tree->GetNextChild(item, cookie);
        }
    }
}

DuplicateObjectCommand::~DuplicateObjectCommand(){

}

void DuplicateObjectCommand::performAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        int targetId;
        if(itemInfo[i].parentId == -1){
            targetId = -1;
        }else{
            targetId = itemInfo[itemInfo[i].parentId].newItem;
        }

        wxTreeItemId targetItem;
        if(targetId == -1){
            targetItem = tree->GetRootItem();
        }else{
            targetItem = tree->getItem(targetId);
        }

        if(!ran){
            wxTreeItemId newItem = tree->AppendItem(targetItem, itemInfo[i].text);
            itemInfo[i].newItem = tree->addItem(newItem);
        }else{
            wxTreeItemId newItem = tree->AppendItem(targetItem, itemInfo[i].text);
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
