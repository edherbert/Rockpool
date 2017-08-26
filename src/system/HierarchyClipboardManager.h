#ifndef HIERARCHYCLIPBOARDMANAGER_H
#define HIERARCHYCLIPBOARDMANAGER_H

#include <wx/treebase.h>

class HierarchyTree;

class HierarchyClipboardManager
{
    public:
        HierarchyClipboardManager(HierarchyTree *tree);
        virtual ~HierarchyClipboardManager();

        void copyItems(const wxArrayTreeItemIds &items);
        void clearClipboard();

    protected:

    private:
        HierarchyTree *tree;
};

#endif // HIERARCHYCLIPBOARDMANAGER_H
