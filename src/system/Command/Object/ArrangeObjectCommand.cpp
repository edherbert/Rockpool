#include "ArrangeObjectCommand.h"

ArrangeObjectCommand::ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, wxArrayTreeItemIds items) : ObjectCommand(tree){
    this->destination = destination;

    //Each item will need to know where it's original parent was, as well as where it's new parent is.
    //All the ids including the old parent will need to be updated when they are changed.
    //The items will need to be catologed according to their selection, just like before.
    //The command will need to be provided with the target item parent

    //It's proving to be quite difficult to keep track of both the original parent id and the new one.
    //This could be because some of the functions are changing the ids and so on.
    //Simplistically, the function needs to keep a list of items and swap them between the new destination and the old destination.
    //One thing that makes this more complicated is the parenting system
    //How would you keep track of each parent if it's further down the child hierarchy.
    //I think the best way to solve this issue would be to create a separate list of objects, without any reference to their ids.
    //This list would just store the layout of the objects and not worry about their implementation.

    //Each item would have it's text, an int id and an int representing it's parent.
    //If the item was a root item, it would have an id of -1.
    //So the first item which would be a parent would be added and given an id of 0 and a parent id of -1.
    //Then one of it's child items might be added, which would be given an id of 1 and a parent of 0.
    //This would continue until each item has a parent and everything.
    //Then, when it comes time to copy the item over, you could just go through this list and add the items to their destination.

    //Thinking about that, I might still have to contain the current id of each item.
    //This is so that I know what form the item currently takes.
    //This would be for deleting and the check function.


    //Creating the list would involve going through the selection.
    //Each item would have the function that checks for it's children ran on it.
    //Each time a function like this runs, the id count will increase.
    //The function that checks for children will take the id of the parent as a parameter, and then assign it to the parents it adds.

    //Things that will need to change:
        //the destination
        //all the id items
        //the origin

    //Each selected item will need to store it's original location.


    for(int i = 0; i < items.size(); i++){
        ItemInformation info;
        info.id = idCount;
        info.text = tree->GetItemText(items[i]);
        info.parentId = -1;
        info.item = items[i];
        info.originItem = tree->GetItemParent(items[i]);

        itemInfo.push_back(info);
        idCount++;

        searchItem(items[i], info.id);
    }
    for(ItemInformation info : itemInfo){
        std::cout << info.id << std::endl;
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
            info.item = ch;

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
    done = false;
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            tree->Delete(itemInfo[i].item);
        }

        wxTreeItemId targetItem;
        if(itemInfo[i].parentId == -1){
            targetItem = destination;
        }else{
            targetItem = itemInfo[itemInfo[i].parentId].item;
        }

        wxTreeItemId oldId = itemInfo[i].item;
        itemInfo[i].item = tree->AppendItem(targetItem, itemInfo[i].text);

        //checkItems(oldId, itemInfo[i].item);
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, itemInfo[i].item);
    }
    done = true;
}

void ArrangeObjectCommand::performAntiAction(){
    done = false;
    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].parentId == -1){
            tree->Delete(itemInfo[i].item);
        }

        wxTreeItemId targetItem;
        if(itemInfo[i].parentId == -1){
            targetItem = itemInfo[i].originItem;
        }else{
            targetItem = itemInfo[itemInfo[i].parentId].item;
        }

        wxTreeItemId oldId = itemInfo[i].item;
        itemInfo[i].item = tree->AppendItem(targetItem, itemInfo[i].text);

        //checkItems(oldId, itemInfo[i].item);
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, itemInfo[i].item);

        //There is a bug when one item from one area is moved to another and then undone twice.
        //I assume that's because the two ids are conflicting with each other.
    }
    done = true;
}

void ArrangeObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
    if(!done)return;

    if(destination == oldId) destination = newId;

    for(int i = 0; i < itemInfo.size(); i++){
        if(itemInfo[i].originItem == oldId && itemInfo[i].parentId == -1){
            itemInfo[i].originItem = newId;
        }
        if(itemInfo[i].item == oldId){
            itemInfo[i].item = newId;
        }
    }
}
