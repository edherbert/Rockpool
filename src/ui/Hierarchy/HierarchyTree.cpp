#include "HierarchyTree.h"

#include "../../system/Command/Object/ArrangeObjectCommand.h"
#include "HierarchyRightClickMenu.h"
#include "../../map/Main.h"
#include "../../system/Command/CommandManager.h"
#include "HierarchyObjectInformation.h"
#include "../GLCanvas.h"
#include "../../system/HierarchyClipboardManager.h"

HierarchyTree::HierarchyTree(ObjectHierarchy *objectHierarchy) : wxTreeCtrl(objectHierarchy, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    this->objectHierarchy = objectHierarchy;

    this->clipboard = new HierarchyClipboardManager(this);

    //You can't actually see this in the hierarchy, but it's the root object
    //This is given object data when the map starts.
    AddRoot("Hierarchy");

    wxTreeItemId root = GetRootItem();

    /*wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    AppendItem(triangle, "other triangle");*/

    /*for(int y = 0; y < 10; y++){
        wxTreeItemId yVal = AppendItem(root, std::to_string(y));
        addItem(yVal);
        for(int x = 0; x < 10; x++){
            wxTreeItemId xVal = AppendItem(yVal, std::to_string(x));
            addItem(xVal);
            for(int z = 0; z < 10; z++){
                wxTreeItemId zVal = AppendItem(xVal, std::to_string(z));
                addItem(zVal);
            }
        }
    }*/

    Connect(wxEVT_MOTION, wxMouseEventHandler(HierarchyTree::mouseMoved));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(HierarchyTree::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(HierarchyTree::mouseUp));
    Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(HierarchyTree::mouseRightDown));

    Connect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(HierarchyTree::selectionChanged));
}

HierarchyTree::~HierarchyTree(){

}

void HierarchyTree::setMap(Map *map){
    this->map = map;
}

Map* HierarchyTree::getMap(){
    return map;
}

void HierarchyTree::selectionChanged(wxTreeEvent &event){
    selectionChanged();
}

void HierarchyTree::selectionChanged(){
    std::cout << "Selection Change" << std::endl;

    map->updateCurrentSelection();
}

ObjectHierarchy* HierarchyTree::getObjectHierarchy(){
    return objectHierarchy;
}

void HierarchyTree::mouseMoved(wxMouseEvent &event){
    //std::cout << event.GetPosition().y << std::endl;
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
        updateDragAnim(location);
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
        selectionChanged();
    }
}

void HierarchyTree::mouseUp(wxMouseEvent &event){
    //Regardless of what happens, checked location is set to false when the mouse button is raised.
    checkedLocation = false;
    //If there are no items, then that means nothing was dragged
    if(currentItems.size() <= 0)return;

    /*bool validMove = false;
    if(currentDestination.IsOk()){
        //If an item is not being dragged into one of it's children.
        if(!checkItemParent(currentDestination)){
            validMove = true;
        }
    }

    //If all the items are ok and there are no restrictions of any kind then move the item.
    if(validMove){
        ItemDragDestinationInfo info = processItemDestination();

        ArrangeObjectCommand *command = new ArrangeObjectCommand(this, info.actualDestination, info.index, currentItems);
        //command->performAction();
        getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
    }*/

    bool validMove = false;
    if(currentDestination.IsOk()){
        //If an item is not being dragged into one of it's children.
        if(!checkItemParent(currentDestination)){
            validMove = true;
        }
    }

    if(validMove){
        ItemDragDestinationInfo info = processItemDestination();

        ArrangeObjectCommand *command = new ArrangeObjectCommand(this, info.actualDestination, info.index, currentItems);

        getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
    }

    endDrag();
}

ItemDragDestinationInfo HierarchyTree::processItemDestination(){
    //This function assumes the move is valid
    wxTreeItemId actualDestination;
    int index = 0;
    if(currentHoverState == hoverStateInside){
        actualDestination = currentDestination;
        index = GetChildrenCount(actualDestination, false);
    }else if(currentHoverState == hoverStateBelow){
        actualDestination = GetItemParent(currentDestination);
        index = getItemIndex(actualDestination, currentDestination) + 1;
    }else if(currentHoverState == hoverStateAbove){
        actualDestination = GetItemParent(currentDestination);
        index = getItemIndex(actualDestination, currentDestination);
    }

    //For the regular drag, it should be checked if the item is ok.
    //If it's not then do nothing.
    //For the resource drag, if the item isn't ok then it needs to be put into the root object.
    //So basically just this function within the valid move bit.

    ItemDragDestinationInfo info;
    info.actualDestination = actualDestination;
    info.index = index;
    info.validMove = false;

    return info;
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

//Check if any of the items that are parent to this item are selected.
bool HierarchyTree::isParentSelected(wxTreeItemId item){
    wxTreeItemId currentItem = GetItemParent(item);
    while(currentItem != GetRootItem()){
        if(IsSelected(currentItem)){
            return true;
        }
        currentItem = GetItemParent(currentItem);
    }
    return false;
}

void HierarchyTree::mouseRightDown(wxMouseEvent &event){
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

//Check if this is still used
wxTreeItemId HierarchyTree::AddObject(Object *object, wxString name, wxTreeItemId parent){
    if(parent == 0){
        parent = GetRootItem();

        //getMap()->getSceneManager()->getRootSceneNode()->addChild(object->getSceneNode());
    }
    return AppendItem(parent, name);
}

void HierarchyTree::removeObject(wxTreeItemId item){
    Delete(item);
}

int HierarchyTree::addItem(wxTreeItemId item){
    itemList.push_back(item);
    return itemList.size() - 1;
}

void HierarchyTree::setItem(int id, wxTreeItemId item){
    itemList[id] = item;
}

wxTreeItemId HierarchyTree::getItem(int id){
    return itemList[id];
}

int HierarchyTree::getId(wxTreeItemId item){
    for(int i = 0; i < itemList.size(); i++){
        if(itemList[i] == item){
            return i;
        }
    }
    return -1;
}

int HierarchyTree::getItemIndex(wxTreeItemId target, wxTreeItemId item){
    int count = 0;
    if(ItemHasChildren(target)){
        wxTreeItemIdValue cookie;
        wxTreeItemId ch = GetFirstChild(target, cookie);
        while(ch != item){
            count++;
            ch = GetNextChild(target, cookie);
        }
    }
    return count;
}

void HierarchyTree::beginResourceDrag(const wxString &itemName){
    if(resourceItemDrag) return;

    resourceItemDrag = true;
    this->itemDragName = itemName;
}

void HierarchyTree::endResourceDrag(){
    if(!resourceItemDrag) return;

    wxTreeItemId destination;
    int index;

    bool validMove = false;
    //If there is a current destionation
    if(currentDestination.IsOk()){
        //Get all the information regarding it's drag
        ItemDragDestinationInfo info = processItemDestination();

        destination = info.actualDestination;
        index = info.index;
        validMove = true;
    }else{
        //If the mouse is within the object hierarchy, then just append to the root.
        wxPoint mousePos = wxGetMousePosition();
        wxRect rect = GetScreenRect();

        if(mousePos.x >= rect.GetLeft() && mousePos.x <= rect.GetRight() && mousePos.y >= rect.GetTop() && mousePos.y <= rect.GetBottom()){
            destination = GetRootItem();
            index = GetChildrenCount(GetRootItem(), false);
            validMove = true;
        }
    }

    if(validMove){
        AddObjectCommand *command = new AddObjectCommand(itemDragName, itemDragName, this, getId(destination), index);
        command->performAction();

        getObjectHierarchy()->getMainFrame()->getMain()->getCommandManager()->pushCommand(command);
    }

    resourceItemDrag = false;
    endDrag();

    getObjectHierarchy()->getMainFrame()->getCanvas()->renderFrame();
}

void HierarchyTree::updateResourceDrag(){
    if(!resourceItemDrag) return;

    wxMouseState state = wxGetMouseState();
    int newMouseX = state.GetPosition().x - GetScreenPosition().x;
    int newMouseY = state.GetPosition().y - GetScreenPosition().y;

    updateDragAnim(wxPoint(newMouseX, newMouseY));
}

void HierarchyTree::updateDragAnim(const wxPoint &location){
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
        //if(currentHoverState == hoverStateInside) SetItemDropHighlight(item);
        if(currentHoverState == hoverStateInside) SetItemBackgroundColour(item, wxColour("#FF0000"));
        else SetItemBackgroundColour(item, wxColour("#FFFFFF"));
    }else{
        //If there is something wrong with the item being hovered over, reset the highlight.
        resetItemHighlight();
    }
}

HierarchyClipboardManager* HierarchyTree::getClipboardManager(){
    return clipboard;
}

int HierarchyTree::getSelectionCount(){
    wxArrayTreeItemIds items;
    GetSelections(items);

    return items.size();
}

std::vector<Object*> HierarchyTree::getSelectedObjects(bool includeChildrenOfSelected){
    wxArrayTreeItemIds items;
    GetSelections(items);

    std::vector<Object*> returnItems;

    for(int i = 0; i < items.size(); i++){
        if(!includeChildrenOfSelected && isParentSelected(items[i])) continue;

        //Get the object and push it to the return list.
        returnItems.push_back(((HierarchyObjectInformation*)GetItemData(items[i]))->getObject());
    }
    return returnItems;
}

Object* HierarchyTree::getFirstSelectionObject(){
    wxArrayTreeItemIds items;
    GetSelections(items);

    if(items.size() > 0){
        return ((HierarchyObjectInformation*)GetItemData(items[0]))->getObject();
    }else{
        return 0;
    }
}
