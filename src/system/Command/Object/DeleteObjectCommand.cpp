#include "DeleteObjectCommand.h"

DeleteObjectCommand::DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items) : ObjectCommand(tree){
    wxArrayTreeItemIds newItems;

    for(wxTreeItemId item : items){
        //Check to see if the item is already in the list
        //This prevents a bug where selected items are added to the list, even if the child item search has already added them.
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
                //The delete command is only run on the selected items. Their children are deleted with them.
                //If one of an item's parents is selected, the item will be deleted anyway, so remove it from the selected items.
                //This prevents a bug where the system tries to delete an item that's already been deleted by the removal of it's parent.
                objectInfo[i].selected = false;
            }
        }
    }
}

DeleteObjectCommand::~DeleteObjectCommand(){

}

void DeleteObjectCommand::performAction(){
    for(ObjectInformation info : objectInfo){
        if(info.selected){
            tree->Delete(info.id);
        }
    }
}

void DeleteObjectCommand::performAntiAction(){
    for(int i = 0; i < objectInfo.size(); i++){
        wxTreeItemId oldId = objectInfo[i].id;
        objectInfo[i].id = tree->AppendItem(objectInfo[i].parentId, objectInfo[i].text);

        //Once a new item is appended, go through the list again and update all the parent values that match this one.
        //Some items will need the new parent value in order to be appended
        tree->getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->updateObjectCommands(oldId, objectInfo[i].id);
    }
}

void DeleteObjectCommand::checkItems(wxTreeItemId oldId, wxTreeItemId newId){
    for(int i = 0; i < objectInfo.size(); i++){
        if(objectInfo[i].parentId == oldId){
            objectInfo[i].parentId = newId;
        }
        if(objectInfo[i].id == oldId){
            objectInfo[i].id = newId;
        }
    }
}
