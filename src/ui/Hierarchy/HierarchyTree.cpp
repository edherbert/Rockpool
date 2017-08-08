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
/*
//This makes it so the drag only happens if the mouse is moved, not just for a click.
//This checks for the item to drag.
//It only runs once, because checkedLocation determines if the drag found anything.
//If the user clicked on nothing, then nothing gets selected, but the check won't be run until they lift the mouse button.
//This prevents a bug where the user could click a void area and then drag the mouse onto an entry to start dragging it.
    if(wxGetMouseState().LeftDown() && !currentSelected && !checkedLocation){
        wxPoint location = event.GetPosition();

        wxTreeItemId item = HitTest(location);
        if(item.IsOk()){
            currentSelected = item;
            std::cout << "Dragging item" << GetItemText(item) << std::endl;
        }
        checkedLocation = true;
    }
    //Something is being dragged, so do all the highlights
    if(currentSelected){
        wxPoint location = event.GetPosition();
        wxTreeItemId item = HitTest(location);

        if(item.IsOk()){
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
            //If no item is being dragged, do nothing.
            resetItemHighlight();
        }
    }
*/
    //if(wxGetMouseState().LeftDown() && !checkedLocation && !currentSelection){
    if(wxGetMouseState().LeftDown() && !checkedLocation){
        wxArrayTreeItemIds items;
        GetSelections(items);

        wxPoint location = event.GetPosition();

        /*wxTreeItemId item = HitTest(location);
        if(item.IsOk()){
            currentSelected = item;
            std::cout << "Dragging item" << GetItemText(item) << std::endl;
        }*/
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
/*
//If there is no item to drop the thing onto, like outside the tree then there will be a crash.
    if(currentSelected){
        if(aboveDestination){
            wxTreeItemId parentDestination = GetPrevSibling(currentDestination);
            if(parentDestination.IsOk()){
                if(parentDestination == currentSelected || currentDestination == currentSelected){
                    std::cout << "The items are the same, doing nothing" << std::endl;
                }else{
                    std::cout << "Dropping below " << GetItemText(parentDestination) << std::endl;
                }
            }else{
                if(currentDestination.IsOk()){
                    if(currentSelected == currentDestination){
                        std::cout << "The items are the same, doing nothing" << std::endl;
                    }else{
                        std::cout << "Dropping above " << GetItemText(currentDestination) << std::endl;
                    }
                }
            }
        }else{
            if(currentDestination.IsOk()){
                std::cout << "Dropping onto " << GetItemText(currentDestination) << std::endl;
            }
        }


        currentSelected = 0;
        resetItemHighlight();
        std::cout << "finished drag" << std::endl;
    }
    checkedLocation = false;
    */

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
        std::cout << "moving" << std::endl;
    }


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
