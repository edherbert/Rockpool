#include "HierarchyTree.h"

HierarchyTree::HierarchyTree(wxWindow *parent) : wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_MULTIPLE){
    AddRoot("Hierarchy");

    wxTreeItemId root = GetRootItem();
    wxTreeItemId cube = AppendItem(root, "Cube");
    wxTreeItemId sphere = AppendItem(root, "Sphere");
    wxTreeItemId triangle = AppendItem(root, "Triangle");

    //SetItemDropHighlight(cube, true);


    AppendItem(triangle, "other triangle");

    Connect(wxEVT_TREE_BEGIN_DRAG, wxTreeEventHandler(HierarchyTree::dragBegin));
    Connect(wxEVT_TREE_END_DRAG, wxTreeEventHandler(HierarchyTree::dragEnd));
}

HierarchyTree::~HierarchyTree(){

}

void HierarchyTree::dragBegin(wxTreeEvent &event){
    if(event.GetItem() == GetRootItem()) return;

    std::cout << "dragging" << std::endl;
    draggedItem = event.GetItem();
    event.Allow();
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
