#ifndef DELETEOBJECTCOMMAND_H
#define DELETEOBJECTCOMMAND_H

#include "ObjectCommand.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

struct ItemInformation;

class DeleteObjectCommand : public ObjectCommand
{
    public:
        DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DeleteObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:

        void searchItem(wxTreeItemId item, int parentId);

        int idCount = 0;

        std::vector<ObjectInformation> objectInfo;
        std::vector<ItemInformation> itemInfo;
};

#endif // DELETEOBJECTCOMMAND_H
