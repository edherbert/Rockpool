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
        Object* copyObject(Object *object);
        void clearClipboard();
        bool containsItems();

        const copyInfo& getCopyInfoItem(int index);
        int getItemInfoSize();

    protected:

    private:
        HierarchyTree *tree;

        int idCount = 0;

        std::vector<copyInfo> itemInfo;

        void searchItem(wxTreeItemId item, int parentId);
};

#endif // HIERARCHYCLIPBOARDMANAGER_H
