#include "HierarchyTree.h"

HierarchyTree::HierarchyTree(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    //You can't actually see this in the hierarchy, but it's the root object
    AddRoot("Hierarchy");

    /*wxTreeItemId root = GetRootItem();
    wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    AppendItem(triangle, "other triangle");*/

    /*for(int y = 0; y < 10; y++){
        wxTreeItemId yVal = AppendItem(root, std::to_string(y));
        for(int x = 0; x < 10; x++){
            wxTreeItemId xVal = AppendItem(yVal, std::to_string(x));
            for(int z = 0; z < 10; z++){
                wxTreeItemId zVal = AppendItem(xVal, std::to_string(z));
            }
        }
    }*/

    Connect(wxEVT_MOTION, wxMouseEventHandler(HierarchyTree::mouseMoved));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(HierarchyTree::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(HierarchyTree::mouseUp));

    Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(HierarchyTree::MouseRightDown));
}

HierarchyTree::~HierarchyTree(){

}

void HierarchyTree::setMap(Map *map){
    this->map = map;
}

Map* HierarchyTree::getMap(){
    return map;
}

void HierarchyTree::mouseMoved(wxMouseEvent &event){
    //Checked location is run the first time the mouse is pressed down
    //It makes sure the user can't click on an invalid area, then move their mouse and still have the checks take place
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
            if(currentHoverState == hoverStateInside) SetItemDropHighlight(item);
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

    wxPoint location = event.GetPosition();
    wxTreeItemId item = HitTest(location);

    if(!item.IsOk()){
        UnselectAll();
        endDrag();
        checkedLocation = true;
    }
}

void HierarchyTree::mouseUp(wxMouseEvent &event){
//Regardless of what happens, checked location is set to false when the mouse button is raised.
    checkedLocation = false;
//If there are no items, then that means nothing was dragged
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
        //Go through all the items
        for(int i = currentItems.size() - 1; i >= 0; i--){
            wxTreeItemId newItem;
            if(currentHoverState == hoverStateBelow){
                newItem = InsertItem(GetItemParent(currentDestination), currentDestination, GetItemText(currentItems[i]));
            }else if(currentHoverState == hoverStateAbove){
                newItem = InsertItem(GetItemParent(currentDestination), GetPrevSibling(currentDestination), GetItemText(currentItems[i]));
            }else if(currentHoverState == hoverStateInside){
                newItem = AppendItem(currentDestination, GetItemText(currentItems[i]));
            }

            //This function checks if the item being dragged has children, and then copies them over
            checkAppendItemTree(newItem, currentItems[i]);
            //Remove the old item when teh drag has finished.
            Delete(currentItems[i]);
        }
    }

    endDrag();
}

void HierarchyTree::endDrag(){
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

//The destination object (the one that has items appended to it), and the one that's currently being searched
void HierarchyTree::checkAppendItemTree(wxTreeItemId destination, wxTreeItemId item){
    if(ItemHasChildren(item)){
        //This will loop through the children.
        //The cookie is used to store the iteration values
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = GetFirstChild(item, cookie);
        while(ch.IsOk()){
            //Append the text to the destination (this will run for each child)
            wxTreeItemId newItem = AppendItem(destination, GetItemText(ch));
            //Check if that child has children and do the same for them.
            checkAppendItemTree(newItem, ch);

            ch = GetNextChild(item, cookie);
        }
    }
}

void HierarchyTree::MouseRightDown(wxMouseEvent &event){
    event.Skip();
    if(!map) return;

    wxPoint location = event.GetPosition();
    wxTreeItemId item = HitTest(location);

    if(item.IsOk()){
        if(!IsSelected(item)){
            UnselectAll();
            SelectItem(item);
        }
     }else{
        UnselectAll();
     }

    wxArrayTreeItemIds items;
    GetSelections(items);

    HierarchyRightClickMenu* menu = new HierarchyRightClickMenu(this, location, items);
    menu->popup();
}

void HierarchyTree::AddObject(Object *object, wxString name, wxTreeItemId parent){
    if(parent == 0){
        parent = GetRootItem();
    }
    AppendItem(parent, name);
}
