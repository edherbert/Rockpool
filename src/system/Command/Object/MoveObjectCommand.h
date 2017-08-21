#ifndef MOVEOBJECTCOMMAND_H
#define MOVEOBJECTCOMMAND_H

#include "ObjectCommand.h"

class HierarchyTree;

class MoveObjectCommand : public ObjectCommand
{
    public:
        MoveObjectCommand(HierarchyTree *tree);
        virtual ~MoveObjectCommand();

        void update(int x, int y);

    protected:

    private:
};

#endif // MOVEOBJECTCOMMAND_H
