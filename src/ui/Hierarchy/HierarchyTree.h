#ifndef HIERARCHYTREE_H
#define HIERARCHYTREE_H

#include "ObjectHierarchy.h"
#include "HierarchyRightClickMenu.h"
#include <wx/treectrl.h>

#include "../../map/Object/Object.h"
#include "../../map/Map.h"

enum itemHoverState{
    hoverStateAbove,
    hoverStateBelow,
    hoverStateInside,
};

class Map;
class ObjectHierarchy;

class HierarchyTree : public wxTreeCtrl
{
    public:
        HierarchyTree(ObjectHierarchy *objectHierarchy);
        virtual ~HierarchyTree();

        wxTreeItemId AddObject(Object *object, wxString name, wxTreeItemId parent = 0);
        void removeObject(wxTreeItemId item);

        void setMap(Map *map);
        Map* getMap();
        ObjectHierarchy* getObjectHierarchy();

    protected:

    private:
        void mouseDown(wxMouseEvent &event);
        void mouseUp(wxMouseEvent &event);

        void MouseRightDown(wxMouseEvent &event);

        void mouseMoved(wxMouseEvent &event);

        void resetItemHighlight();
        void checkAppendItemTree(wxTreeItemId destination, wxTreeItemId item);
        void endDrag();

        itemHoverState currentHoverState;
        wxTreeItemId currentDestination;

        Map *map = 0;
        ObjectHierarchy *objectHierarchy = 0;

        bool checkItemParent(wxTreeItemId item);

        bool checkedLocation = false;
        wxArrayTreeItemIds currentItems;
};

#endif // HIERARCHYTREE_H
