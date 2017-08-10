#ifndef HIERARCHYTREE_H
#define HIERARCHYTREE_H

#include "ObjectHierarchy.h"
#include "HierarchyRightClickMenu.h"
#include <wx/treectrl.h>

enum itemHoverState{
    hoverStateAbove,
    hoverStateBelow,
    hoverStateInside,
};

class HierarchyTree : public wxTreeCtrl
{
    public:
        HierarchyTree(wxWindow *parent);
        virtual ~HierarchyTree();

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

        bool checkItemParent(wxTreeItemId item);

        bool checkedLocation = false;
        wxArrayTreeItemIds currentItems;
};

#endif // HIERARCHYTREE_H
