#ifndef DUPLICATEOBJECTCOMMAND_H
#define DUPLICATEOBJECTCOMMAND_H

#include "ObjectCommand.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

class DuplicateObjectCommand : public ObjectCommand
{
    public:
        DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DuplicateObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
};

#endif // DUPLICATEOBJECTCOMMAND_H
