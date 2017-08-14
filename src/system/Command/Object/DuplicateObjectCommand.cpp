#include "DuplicateObjectCommand.h"

DuplicateObjectCommand::DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){
    wxArrayTreeItemIds newItems;

    for(wxTreeItemId item : items){
        bool found = false;
        for(wxTreeItemId checkItem : newItems){
            if(checkItem == item)found = true;
        }

        if(!found){
            tree->getItemsAndAppend(&newItems, item);
        }
    }

    for(wxTreeItemId item : newItems){
        ObjectInformation info;
        info.text = tree->GetItemText(item);
        info.parentId = tree->GetItemParent(item);
        info.id = item;
        info.selected = tree->IsSelected(item);

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

DuplicateObjectCommand::~DuplicateObjectCommand(){

}

void DuplicateObjectCommand::performAction(){
    for(int i = 0; i < objectInfo.size(); i++){
        wxTreeItemId oldId = objectInfo[i].id;
        objectInfo[i].id = tree->AppendItem(objectInfo[i].parentId, objectInfo[i].text);

        //This function might be run before the command is added to the command manager.
        //For this reason, check items is run once more, just to make sure that is was run.
        //It's important to make sure that the children of each item are copied over correctly.
        checkItems(oldId, objectInfo[i].id);
        if(ran)tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, objectInfo[i].id);
    }
    //This is a check so that the function to update the other items only happens the second time this is run.
    //Remember that this function works by duplicating items
    //If the function to update the other commands happens, it will also replace the commands that were supposed to target the original item.
    //So basically, only update the commands after the new, duplicate ones have been fully created.
    ran = true;
}

void DuplicateObjectCommand::performAntiAction(){
    for(ObjectInformation info : objectInfo){
        if(info.selected){
            tree->Delete(info.id);
        }
    }
}

void DuplicateObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
    for(int i = 0; i < objectInfo.size(); i++){
        if(objectInfo[i].parentId == oldId){
            objectInfo[i].parentId = newId;
        }
        if(objectInfo[i].id == oldId){
            objectInfo[i].id = newId;
        }
    }
}
