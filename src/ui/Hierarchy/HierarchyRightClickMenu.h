#ifndef HIERARCHYRIGHTCLICKMENU_H
#define HIERARCHYRIGHTCLICKMENU_H

#include <wx/wx.h>
#include <wx/treectrl.h>
#include "../wxIDs.h"
#include "HierarchyRightClickNew.h"

#include "../../system/Command/Object/DeleteObjectCommand.h"
#include "../../system/Command/Object/DuplicateObjectCommand.h"

class HierarchyRightClickMenu : public wxMenu
{
    public:
        HierarchyRightClickMenu(HierarchyTree *hierarchyTree, wxPoint location, const wxArrayTreeItemIds &selection);
        virtual ~HierarchyRightClickMenu();

        void popup();

    protected:

    private:
        HierarchyTree *hierarchyTree;
        wxPoint location;
        wxArrayTreeItemIds selection;

        void itemClick(wxCommandEvent &event);
};

#endif // HIERARCHYRIGHTCLICKMENU_H
