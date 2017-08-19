#ifndef DUPLICATEOBJECTCOMMAND_H
#define DUPLICATEOBJECTCOMMAND_H

#include "ObjectCommand.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

struct ItemInformation;

class DuplicateObjectCommand : public ObjectCommand
{
    public:
        DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DuplicateObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        std::vector<ObjectInformation> objectInfo;
        std::vector<ItemInformation> itemInfo;

        void searchItem(wxTreeItemId item, int parentId);

        bool ran = false;
        int idCount = 0;
};

#endif // DUPLICATEOBJECTCOMMAND_H
