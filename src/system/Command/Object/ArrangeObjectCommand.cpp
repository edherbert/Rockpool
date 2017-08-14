#include "ArrangeObjectCommand.h"

ArrangeObjectCommand::ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, wxArrayTreeItemIds items) : ObjectCommand(tree){
    this->destination = destination;

    //Each item will need to know where it's original parent was, as well as where it's new parent is.
    //All the ids including the old parent will need to be updated when they are changed.
    //The items will need to be catologed according to their selection, just like before.
    //The command will need to be provided with the target item parent

    wxArrayTreeItemIds newItems;

    for(wxTreeItemId item : items){
        bool found = false;
        //Checks if an item is going to be added twice
        for(wxTreeItemId checkItem : newItems){
            if(checkItem == item)found = true;
        }

        if(!found){
            tree->getItemsAndAppend(&newItems, item);
        }
    }

    for(wxTreeItemId item : newItems){
        ArrangeInformation info;
        info.text = tree->GetItemText(item);
        info.originalParentId = tree->GetItemParent(item);
        info.id = item;
        info.selected = tree->IsSelected(item);

        if(info.selected){
            info.parentId = destination;
        }else{
            info.parentId = tree->GetItemParent(item);
        }

        objectInfo.push_back(info);
    }

    for(int i = 0; i < objectInfo.size(); i++){
        if(objectInfo[i].selected){
            if(tree->isParentSelected(objectInfo[i].id)){
                objectInfo[i].selected = false;
            }
        }
    }
}

ArrangeObjectCommand::~ArrangeObjectCommand(){

}

void ArrangeObjectCommand::performAction(){
    for(int i = 0; i < objectInfo.size(); i++){
        wxTreeItemId oldId = objectInfo[i].id;
        if(objectInfo[i].selected){
            tree->Delete(oldId);
        }

        objectInfo[i].id = tree->AppendItem(objectInfo[i].parentId, objectInfo[i].text);

        if(ran)checkItems(oldId, objectInfo[i].id);
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, objectInfo[i].id);

        //The destination is only for the root objects, so it can't be set as the parent for every item.
        //Go through and set the current parent, based on the current position.
        //Then, when going through

        //The original destination can be set, but the new one can't.
        //When a new item is created, go through only the new parent ids
        //if it's equal to the old id, replace it.
    }
    ran = true;
}

void ArrangeObjectCommand::performAntiAction(){
    for(int i = 0; i < objectInfo.size(); i++){
        wxTreeItemId oldId = objectInfo[i].id;
        if(objectInfo[i].selected){
            tree->Delete(oldId);
        }

        objectInfo[i].id = tree->AppendItem(objectInfo[i].originalParentId, objectInfo[i].text);

        checkItems(oldId, objectInfo[i].id);
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, objectInfo[i].id);
    }
}

void ArrangeObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
    for(int i = 0; i < objectInfo.size(); i++){
        if(objectInfo[i].parentId == oldId){
            objectInfo[i].parentId = newId;
        }
        if(objectInfo[i].id == oldId){
            objectInfo[i].id = newId;
        }
        if(ran && objectInfo[i].originalParentId == oldId){
            objectInfo[i].originalParentId = newId;
        }
    }
}
