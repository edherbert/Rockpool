#include "ArrangeObjectCommand.h"

ArrangeObjectCommand::ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, int destinationIndex, wxArrayTreeItemIds items) : ObjectCommand(tree){
    this->destination = tree->getId(destination);
    this->destinationIndex = destinationIndex;

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

    //There is a bug with the dragging.
    //I think it's when an item is dragged
    //Move multiple items into one item, and then another, then move them back

    //Move two items into one item and then another. Move the items back to the first item. This causes a crash. This only happens when moving multiple items.
    //Move two items into one item and then another. Move the items back to the first item, then delte it. Attempting to undo this causes a crash.

    //These sorts of crashes don't happen all the time, so I can assume it's something to do with the ids.
    //Of course, the function to find an id just finds the id, even if there are multiple in the vector.
    //I might have to make some sort of check for this kind of thing.
    //I think this is the last major bug in the system.

    //There might be a bug where inside items are also being selected.



    //Indexing for the position.
    //The position shouldn't be too hard to deal with.
    //So when the item is moved, you would take the destination as the parent item.
    //If the item is dragged onto an item, then the destination is the the item dragged onto.
    //If the item is dragged below or above an item, then the destination is the parent of that item.

    //I'm going to have to store an origin index but I think I could just store the destination index.
    //
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

        //wxTreeItemId newItem = tree->AppendItem(targetItem, itemInfo[i].text);

        wxTreeItemId newItem;
        if(itemInfo[i].parentId == -1){
            newItem = tree->InsertItem(targetItem, destinationIndex, itemInfo[i].text);
        }else{
            newItem = tree->AppendItem(targetItem, itemInfo[i].text);
        }


        if(!ran){
            itemInfo[i].newItem = tree->addItem(newItem);
        }else{
            tree->setItem(itemInfo[i].newItem, newItem);
        }

        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].originItem));
            tree->setItem(itemInfo[i].originItem, 0);
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

        //On the anti action, if the item is a base item, then insert it by index.
        wxTreeItemId originItem;
        if(itemInfo[i].parentId == -1){
            originItem = tree->InsertItem(targetItem, itemInfo[i].index, itemInfo[i].text);
        }else{
            originItem = tree->AppendItem(targetItem, itemInfo[i].text);
        }

        //wxTreeItemId originItem = tree->AppendItem(targetItem, itemInfo[i].text);
        tree->setItem(itemInfo[i].originItem, originItem);

        if(itemInfo[i].parentId == -1){
            tree->Delete(tree->getItem(itemInfo[i].newItem));
            tree->setItem(itemInfo[i].newItem, 0);
        }
    }
}
