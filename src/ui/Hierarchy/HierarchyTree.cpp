#include "HierarchyTree.h"

HierarchyTree::HierarchyTree(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    AddRoot("Hierarchy");

    wxTreeItemId root = GetRootItem();
    wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    AppendItem(triangle, "other triangle");

    for(int y = 0; y < 10; y++){
        wxTreeItemId yVal = AppendItem(root, std::to_string(y));
        for(int x = 0; x < 10; x++){
            wxTreeItemId xVal = AppendItem(yVal, std::to_string(x));
            for(int z = 0; z < 10; z++){
                wxTreeItemId zVal = AppendItem(xVal, std::to_string(z));
            }
        }
    }

    Connect(wxEVT_MOTION, wxMouseEventHandler(HierarchyTree::mouseMoved));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(HierarchyTree::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(HierarchyTree::mouseUp));
}

HierarchyTree::~HierarchyTree(){

}

void HierarchyTree::mouseMoved(wxMouseEvent &event){
    //if(wxGetMouseState().LeftDown() && !checkedLocation && !currentSelection){
    if(wxGetMouseState().LeftDown() && !checkedLocation){
        wxArrayTreeItemIds items;
        GetSelections(items);

        wxPoint location = event.GetPosition();

        wxTreeItemId item = HitTest(location);
        if(item.IsOk()){
            if(std::find(items.begin(), items.end(), item)){
                currentItems = items;
            }
        }else{
            UnselectAll();
        }
        checkedLocation = true;
    }
    //If there are items in the current items array, then something is being dragged
    if(currentItems.size() > 0){
        wxPoint location = event.GetPosition();
        wxTreeItemId item = HitTest(location);

        //Don't bother doing all this highlight logic if the item is selected or not ok.
        if(item.IsOk() && !IsSelected(item)){
            wxRect rect;
            GetBoundingRect(item, rect);

            int posY = location.y - rect.GetLeftTop().y;
            int border = rect.GetHeight() / 4;
            if(posY < border){
                currentHoverState = hoverStateAbove;
            }
            else if(posY > rect.GetHeight() - border){
                currentHoverState = hoverStateBelow;
            }
            else{
                currentHoverState = hoverStateInside;
            }

            //If the highlighted item has changed
            if(item != currentDestination){
                resetItemHighlight();
                currentDestination = item;
            }
            if(currentHoverState == hoverStateInside) SetItemBackgroundColour(item, wxColour("#FF0000"));
            else SetItemBackgroundColour(item, wxColour("#FFFFFF"));
        }else{
            //If there is something wrong with the item being hovered over, reset the highlight.
            resetItemHighlight();
        }
    }
}

void HierarchyTree::resetItemHighlight(){
    if(currentDestination)SetItemBackgroundColour(currentDestination, wxColour("#FFFFFF"));
    currentDestination = 0;
}

void HierarchyTree::mouseDown(wxMouseEvent &event){
    event.Skip();

    //Abstract this into a function at some point.
    wxPoint location = event.GetPosition();
    wxTreeItemId item = HitTest(location);

    if(!item.IsOk()){
        UnselectAll();
    }
}

void HierarchyTree::mouseUp(wxMouseEvent &event){
    //Parent items can't be dragged into themselves. If any of the items in the selection have this then do nothing for all of them.
    //If the item destination is selected, do nothing. This also covers tryting to drag items into themselves.
    //If the desination is not ok then do nothing.

    if(currentItems.size() <= 0)return;

    bool validMove = false;
    if(currentDestination.IsOk()){
        //If an item is not being dragged into one of it's children.
        if(!checkItemParent(currentDestination)){
            validMove = true;
        }
    }

    //If all the items are ok and there are no restrictions of any kind then move the item.
    if(validMove){
        //If the value is 0 (above), find the item above
            //If there is no item above then copy the item into the first place.
        //If the item is below, do nothing.
        if(currentHoverState == hoverStateBelow){
            //InsertItem(GetItemParent())
            for(int i = currentItems.size() - 1; i >= 0; i--){
                wxTreeItemId newItem = InsertItem(GetItemParent(currentDestination), currentDestination, GetItemText(currentItems[i]));
                checkAppendItemTree(newItem, currentItems[i]);
                Delete(currentItems[i]);
            }
        }
        if(currentHoverState == hoverStateAbove){
            wxTreeItemId sibling = GetPrevSibling(currentDestination);
            for(int i = currentItems.size() - 1; i >= 0; i--){
                wxTreeItemId newItem = InsertItem(GetItemParent(currentDestination), sibling, GetItemText(currentItems[i]));
                checkAppendItemTree(newItem, currentItems[i]);
                Delete(currentItems[i]);
            }
        }
        if(currentHoverState == hoverStateInside){
            for(int i = currentItems.size() - 1; i >= 0; i--){
                wxTreeItemId newItem = AppendItem(currentDestination, GetItemText(currentItems[i]));
                checkAppendItemTree(newItem, currentItems[i]);
                Delete(currentItems[i]);
            }
        }
    }

    //So basically loop through all the children and copy them over
    //If that child has children then run the function on that object.

    //The parent and the location in which the text should be inserted
    //The parent in which the text should be inserted

    //It could just do the job of appending items, rather than inserting them.
    //I could insert the item and then do the search.


    currentItems.clear();
    resetItemHighlight();
    checkedLocation = false;
}


bool HierarchyTree::checkItemParent(wxTreeItemId item){
    //Loop through all the parents of the item until the root is found.
    //Each time go through the current items and see if one of the items is the current parent
    //If it is, then return true, as that means the user is trying to drag an item into itself.
    bool returnVal = false;
    wxTreeItemId currentItem = item;
    while(currentItem != GetRootItem()){
        for(int i = 0; i < currentItems.size(); i++){
            if(currentItems[i] == currentItem){
                returnVal = true;
                return returnVal;
            }
        }
        currentItem = GetItemParent(currentItem);
    }
    return returnVal;
}

//The destination object, and the one that's currently being searched
void HierarchyTree::checkAppendItemTree(wxTreeItemId destination, wxTreeItemId item){
//Make it not immediately append items
    //wxTreeItemId newItem = AppendItem(destination, GetItemText(item));
    if(ItemHasChildren(item)){
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = GetFirstChild(item, cookie);
        while(ch.IsOk()){
            wxTreeItemId newItem = AppendItem(destination, GetItemText(ch));
            checkAppendItemTree(newItem, ch);
            //std::cout << GetItemText(item) << std::endl;
            ch = GetNextChild(item, cookie);
        }
    }
}
