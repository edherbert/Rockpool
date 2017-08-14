#ifndef DELETEOBJECTCOMMAND_H
#define DELETEOBJECTCOMMAND_H

#include "ObjectCommand.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

class DeleteObjectCommand : public ObjectCommand
{
    public:
        DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DeleteObjectCommand();

        void performAction();
        void performAntiAction();

        void checkItems(wxTreeItemId oldId, wxTreeItemId newId);

    protected:

    private:

        std::vector<ObjectInformation> objectInfo;
};

#endif // DELETEOBJECTCOMMAND_H
