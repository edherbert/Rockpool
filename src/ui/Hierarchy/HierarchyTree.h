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

class HierarchyTree : public wxTreeCtrl
{
    public:
        HierarchyTree(wxWindow *parent);
        virtual ~HierarchyTree();

        void AddObject(Object *object, wxString name, wxTreeItemId parent = 0);
        void setMap(Map *map);
        Map* getMap();

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

        bool checkItemParent(wxTreeItemId item);

        bool checkedLocation = false;
        wxArrayTreeItemIds currentItems;
};

#endif // HIERARCHYTREE_H
