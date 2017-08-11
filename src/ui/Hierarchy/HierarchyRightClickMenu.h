#ifndef HIERARCHYRIGHTCLICKMENU_H
#define HIERARCHYRIGHTCLICKMENU_H

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "../wxIDs.h"
#include "HierarchyRightClickNew.h"

class HierarchyRightClickMenu : public wxMenu
{
    public:
        HierarchyRightClickMenu(HierarchyTree *hierarchyTree, wxPoint location, wxArrayTreeItemIds selection);
        virtual ~HierarchyRightClickMenu();

        void popup();

    protected:

    private:
        HierarchyTree *hierarchyTree;
        wxPoint location;
};

#endif // HIERARCHYRIGHTCLICKMENU_H
