#ifndef HIERARCHYRIGHTCLICKNEW_H
#define HIERARCHYRIGHTCLICKNEW_H

#include <wx/wx.h>
#include "../wxIDs.h"
#include "HierarchyTree.h"
#include "../../system/Command/Object/AddObjectCommand.h"

class HierarchyTree;

class HierarchyRightClickNew : public wxMenu
{
    public:
        HierarchyRightClickNew(HierarchyTree *hierarchyTree, wxArrayTreeItemIds selection);
        virtual ~HierarchyRightClickNew();

    protected:

    private:
        void addItem(wxCommandEvent &event);

        HierarchyTree *hierarchyTree;
        wxArrayTreeItemIds selection;
};

#endif // HIERARCHYRIGHTCLICKNEW_H
