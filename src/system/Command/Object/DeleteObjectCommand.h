#ifndef DELETEOBJECTCOMMAND_H
#define DELETEOBJECTCOMMAND_H

#include "ObjectCommand.h"

class DeleteObjectCommand : public ObjectCommand
{
    public:
        DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DeleteObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
};

#endif // DELETEOBJECTCOMMAND_H
