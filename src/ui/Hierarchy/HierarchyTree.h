#ifndef HIERARCHYTREE_H
#define HIERARCHYTREE_H

#include "ObjectHierarchy.h"
#include <wx/treectrl.h>

class HierarchyTree : public wxTreeCtrl
{
    public:
        HierarchyTree(wxWindow *parent);
        virtual ~HierarchyTree();

    protected:

    private:
        void dragBegin(wxTreeEvent &event);
        void dragEnd(wxTreeEvent &event);

        void mouseDown(wxMouseEvent &event);
        void mouseUp(wxMouseEvent &event);

        void mouseMoved(wxMouseEvent &event);

        void resetItemHighlight();

        wxTreeItemId draggedItem;
        //An object to keep track of which item is currently highlighted.
        wxTreeItemId currentHighlight;

        bool checkedLocation = false;
        wxTreeItemId currentSelected;
};

#endif // HIERARCHYTREE_H
