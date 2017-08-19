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
        info.selected = tree->IsSelected(item);

        info.originParentItem = tree->getId(tree->GetItemParent(item));
        info.originItem = tree->getId(item);

        objectInfo.push_back(info);
    }

    for(int i = 0; i < objectInfo.size(); i++){
        if(objectInfo[i].selected){
            if(tree->isParentSelected(tree->getItem(objectInfo[i].originItem))){
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
            tree->Delete(tree->getItem(info.originItem));
            tree->setItem(info.originItem, 0);
        }
    }
}

void DeleteObjectCommand::performAntiAction(){
    for(int i = 0; i < objectInfo.size(); i++){
        //objectInfo[i].id = tree->AppendItem(objectInfo[i].parentId, objectInfo[i].text);
        if(objectInfo[i].originParentItem == -1){
            wxTreeItemId newItem = tree->AppendItem(tree->GetRootItem(), objectInfo[i].text);
            tree->setItem(objectInfo[i].originItem, newItem);
        }else{
            wxTreeItemId newItem = tree->AppendItem(tree->getItem(objectInfo[i].originParentItem), objectInfo[i].text);
            tree->setItem(objectInfo[i].originItem, newItem);
        }
    }
}
