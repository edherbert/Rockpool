#include "ArrangeObjectCommand.h"

ArrangeObjectCommand::ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, wxArrayTreeItemIds items) : ObjectCommand(tree){
    this->destination = tree->getId(destination);

    for(int i = 0; i < items.size(); i++){
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

void ArrangeObjectCommand::searchItem(wxTreeItemId item, int parentId){
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

ArrangeObjectCommand::~ArrangeObjectCommand(){

}

void ArrangeObjectCommand::performAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        int targetId;
        if(itemInfo[i].parentId == -1){
            targetId = destination;
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

        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].originItem));
        }
    }
    //This is to initially create the items
    ran = true;
}

void ArrangeObjectCommand::performAntiAction(){
    for(int i = 0; i < itemInfo.size(); i++){
        int targetId;
        if(itemInfo[i].parentId == -1){
            //targetItem = itemInfo[i].originItem;
            targetId = itemInfo[i].originParentItem;
            //This needs to be the parent of the item that was dragged.
        }else{
            targetId = itemInfo[itemInfo[i].parentId].originItem;
        }

        wxTreeItemId targetItem;
        if(targetId == -1){
            targetItem = tree->GetRootItem();
        }else{
            targetItem = tree->getItem(targetId);
        }

        wxTreeItemId originItem = tree->AppendItem(targetItem, itemInfo[i].text);
        tree->setItem(itemInfo[i].originItem, originItem);

        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].newItem));
        }
    }
}

void ArrangeObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
/*
    if(!done)return;

    if(destination.GetID() == oldId.GetID()) destination = newId;

    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].originItem.GetID() == oldId.GetID() && itemInfo[i].parentId == -1){
            itemInfo[i].originItem = newId;
            //std::cout << "original item" << std::endl;
        }
        if(itemInfo[i].item.GetID() == oldId.GetID()){
            itemInfo[i].item = newId;
            if(itemInfo[i].parentId == -1) std::cout << "Replacing " << oldId.GetID() << " with " << newId.GetID() << std::endl;
        }
    }
    */
}
