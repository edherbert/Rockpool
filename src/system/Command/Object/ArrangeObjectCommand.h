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

    int index;

    int originParentItem;
    int originItem;
    int newItem;
};

class ArrangeObjectCommand : public ObjectCommand
{
    public:
        ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, int destinationIndex, wxArrayTreeItemIds items);
        virtual ~ArrangeObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        int destination;
        int destinationIndex;

        int idCount = 0;
        bool ran = false;

        void searchItem(wxTreeItemId item, int parentId);

        std::vector<ItemInformation> itemInfo;
};

#endif // ARRANGEOBJECTCOMMAND_H
