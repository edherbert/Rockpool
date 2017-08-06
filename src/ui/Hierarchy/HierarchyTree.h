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
};

#endif // HIERARCHYTREE_H
