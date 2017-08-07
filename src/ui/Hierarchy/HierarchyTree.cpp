#include "HierarchyTree.h"

HierarchyTree::HierarchyTree(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    AddRoot("Hierarchy");

    wxTreeItemId root = GetRootItem();
    wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    //SetItemDropHighlight(cube, true);


    AppendItem(triangle, "other triangle");

    Connect(wxEVT_MOTION, wxMouseEventHandler(HierarchyTree::mouseMoved));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(HierarchyTree::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(HierarchyTree::mouseUp));

    //Connect(wxEVT_TREE_BEGIN_DRAG, wxTreeEventHandler(HierarchyTree::dragBegin));
    //Connect(wxEVT_TREE_END_DRAG, wxTreeEventHandler(HierarchyTree::dragEnd));
}

HierarchyTree::~HierarchyTree(){

}

void HierarchyTree::dragBegin(wxTreeEvent &event){
    if(event.GetItem() == GetRootItem()) return;
    std::cout << "dragging" << std::endl;

    draggedItem = event.GetItem();

//    currentlyDragging = true;
    //event.Allow();
    std::cout << "draggingggggg" << std::endl;
}

void HierarchyTree::mouseMoved(wxMouseEvent &event){
//This makes it so the drag only happens if the mouse is moved, not just for a click.
//This checks for the item to drag.
//It only runs once, because checkedLocation determines if the drag found anything.
//If the user clicked on nothing, then nothing gets selected, but the check won't be run until they lift the mouse button.
    if(wxGetMouseState().LeftDown() && !currentSelected && !checkedLocation){
        wxPoint location = event.GetPosition();

        wxTreeItemId item = HitTest(location);
        if(item.IsOk()){
            currentSelected = item;
            std::cout << "Dragging item" << GetItemText(item) << std::endl;
        }
        checkedLocation = true;
    }
    //Something is being dragged
    if(currentSelected){
        wxPoint location = event.GetPosition();
        wxTreeItemId item = HitTest(location);

        //If the highlighted item has changed
        if(item.IsOk() && item != currentHighlight){
            resetItemHighlight();
            currentHighlight = item;
            SetItemBackgroundColour(item, wxColour("#FF0000"));
        }
    }
}

void HierarchyTree::resetItemHighlight(){
    if(currentHighlight)SetItemBackgroundColour(currentHighlight, wxColour("#FFFFFF"));
    currentHighlight = 0;
}

void HierarchyTree::mouseDown(wxMouseEvent &event){
    event.Skip();
}

void HierarchyTree::mouseUp(wxMouseEvent &event){
    if(currentSelected){
        currentSelected = 0;
        resetItemHighlight();
        std::cout << "finished drag" << std::endl;
    }
    checkedLocation = false;
}

void HierarchyTree::dragEnd(wxTreeEvent &event){
    std::cout << "drag end" << std::endl;
    wxTreeItemId itemDestination = event.GetItem();

    if(!itemDestination.IsOk())return;

    wxTreeItemId destinationParent;

    if(!ItemHasChildren(itemDestination)){
        //itemDestination = GetItemParent(itemDestination);
        destinationParent = GetItemParent(itemDestination);
    }

    wxString text = GetItemText(draggedItem);

    //AppendItem(itemDestination, text);
    InsertItem(destinationParent, itemDestination, text);
    Delete(draggedItem);

    //I can check the position of the mouse during a drag as well as after it.
    //I can get a bounding rect for each item.
    //Hit test can tell me which item is underneath a certain point, so I could use the mouse position.

    //I can show a highlight for an object, but I can't show the outline. It might be easier to just not show the outline, but also hide the highlight.
    //That way the user would know that the item isn't going to be put in the wrong place.
}
