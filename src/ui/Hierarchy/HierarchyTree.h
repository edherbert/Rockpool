#ifndef HIERARCHYTREE_H
#define HIERARCHYTREE_H

#include "ObjectHierarchy.h"
#include <wx/treectrl.h>

#include "../../map/Object/Object.h"
#include "../../map/Map.h"

class Map;
class ObjectHierarchy;

enum itemHoverState{
    hoverStateAbove,
    hoverStateBelow,
    hoverStateInside,
};

struct ItemDragDestinationInfo{
    wxTreeItemId actualDestination;
    int index;
    bool validMove;
};

class HierarchyTree : public wxTreeCtrl
{
    public:
        HierarchyTree(ObjectHierarchy *objectHierarchy);
        virtual ~HierarchyTree();

        wxTreeItemId AddObject(Object *object, wxString name, wxTreeItemId parent = 0);
        void removeObject(wxTreeItemId item);

        bool isParentSelected(wxTreeItemId item);

        void setMap(Map *map);
        Map* getMap();
        ObjectHierarchy* getObjectHierarchy();

        int addItem(wxTreeItemId item);
        void setItem(int id, wxTreeItemId item);
        wxTreeItemId getItem(int id);
        int getId(wxTreeItemId item);

        int getItemIndex(wxTreeItemId target, wxTreeItemId item);

        void beginResourceDrag(const wxString &itemName);
        void updateResourceDrag();
        void endResourceDrag();

        void updateDragAnim(const wxPoint &location);

    protected:

    private:
        void mouseDown(wxMouseEvent &event);
        void mouseUp(wxMouseEvent &event);
        void MouseRightDown(wxMouseEvent &event);
        void mouseMoved(wxMouseEvent &event);

        void resetItemHighlight();
        void endDrag();

        ItemDragDestinationInfo processItemDestination();

        itemHoverState currentHoverState;
        wxTreeItemId currentDestination;

        Map *map = 0;
        ObjectHierarchy *objectHierarchy = 0;

        bool checkItemParent(wxTreeItemId item);

        bool resourceItemDrag = false;
        wxString itemDragName;

        bool checkedLocation = false;
        wxArrayTreeItemIds currentItems;

        std::vector<wxTreeItemId> itemList;
};

#endif // HIERARCHYTREE_H
