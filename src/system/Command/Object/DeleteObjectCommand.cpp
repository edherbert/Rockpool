#include "DeleteObjectCommand.h"

DeleteObjectCommand::DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){
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

void DeleteObjectCommand::searchItem(wxTreeItemId item, int parentId){
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

DeleteObjectCommand::~DeleteObjectCommand(){

}

void DeleteObjectCommand::performAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].originItem));
            tree->setItem(itemInfo[i].originItem, 0);
        }
    }
}

void DeleteObjectCommand::performAntiAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        wxTreeItemId newItem;
        wxTreeItemId targetItem;

        //Check if the item is one of the base items
        if(itemInfo[i].parentId == -1){
            //If it's parent item is the root, then set that, otherwise set it to the parent item in the struct.
            if(itemInfo[i].originParentItem == -1){
                targetItem = tree->GetRootItem();
            }else{
                targetItem = tree->getItem(itemInfo[i].originParentItem);
            }
        }else{
            //If it's not one of the base items then get the parent item and get it's item
            targetItem = tree->getItem(itemInfo[itemInfo[i].parentId].originItem);
        }

        //Use the insert command if the item is a base item.
        if(itemInfo[i].parentId == -1){
            newItem = tree->InsertItem(targetItem, itemInfo[i].index, itemInfo[i].text);
        }else{
            newItem = tree->AppendItem(targetItem, itemInfo[i].text);
        }
        tree->setItem(itemInfo[i].originItem, newItem);
    }
}
