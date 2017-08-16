#ifndef ARRANGEOBJECTCOMMAND_H
#define ARRANGEOBJECTCOMMAND_H

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "ObjectCommand.h"

struct ArrangeInformation : public ObjectInformation{
    wxTreeItemId originalParentId;
};

struct ItemInformation{
    wxString text;
    int id;
    int parentId;
    wxTreeItemId item;
    wxTreeItemId originItem;
};

class ArrangeObjectCommand : public ObjectCommand
{
    public:
        ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, wxArrayTreeItemIds items);
        virtual ~ArrangeObjectCommand();

        void performAction();
        void performAntiAction();

        void checkItems(wxTreeItemId oldId, wxTreeItemId newId);

    protected:

    private:
        wxTreeItemId destination;

        int idCount = 0;
        bool done = true;

        void searchItem(wxTreeItemId item, int parentId);

        std::vector<ArrangeInformation> objectInfo;
        std::vector<ItemInformation> itemInfo;
};

#endif // ARRANGEOBJECTCOMMAND_H
