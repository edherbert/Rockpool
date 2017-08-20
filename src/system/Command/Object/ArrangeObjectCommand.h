#ifndef ARRANGEOBJECTCOMMAND_H
#define ARRANGEOBJECTCOMMAND_H

#include "ObjectCommand.h"

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

        bool ran = false;

        wxTreeItemId currentAppendItem = 0;
};

#endif // ARRANGEOBJECTCOMMAND_H
