#ifndef HIERARCHYCLIPBOARDMANAGER_H
#define HIERARCHYCLIPBOARDMANAGER_H

#include <wx/treebase.h>
#include <vector>

class HierarchyTree;
class Object;

struct copyInfo{
    wxString text;
    int id;
    int parentId;

    Object *object;
};

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

        int idCount = 0;
        Object* copyObject(const wxTreeItemId &item);

        std::vector<copyInfo> itemInfo;

        void searchItem(wxTreeItemId item, int parentId);
};

#endif // HIERARCHYCLIPBOARDMANAGER_H
