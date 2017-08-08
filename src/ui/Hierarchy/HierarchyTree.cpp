#include "HierarchyTree.h"

HierarchyTree::HierarchyTree(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    AddRoot("Hierarchy");

    wxTreeItemId root = GetRootItem();
    wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    AppendItem(triangle, "other triangle");

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
    if(wxGetMouseState().LeftDown() && !checkedLocation && !currentItems){
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
    //An item is being dragged.
    if(currentItems){
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
    currentItems.clear();
    currentItems = 0;
    checkedLocation = false;
}
