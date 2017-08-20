#ifndef DUPLICATEOBJECTCOMMAND_H
#define DUPLICATEOBJECTCOMMAND_H

#include "ObjectCommand.h"

class DuplicateObjectCommand : public ObjectCommand
{
    public:
        DuplicateObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DuplicateObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        bool ran = false;
};

#endif // DUPLICATEOBJECTCOMMAND_H
