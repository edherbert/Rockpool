#ifndef MOVEOBJECTCOMMAND_H
#define MOVEOBJECTCOMMAND_H

#include "ObjectCommand.h"

#include <Ogre.h>

#include <vector>

class HierarchyTree;
class Object;

struct ObjectValues{
    Object *object;
    Ogre::Vector3 originPosition;
};

class MoveObjectCommand : public ObjectCommand
{
    public:
        MoveObjectCommand(HierarchyTree *tree);
        virtual ~MoveObjectCommand();

        void update(int x, int y);

        void performAction();
        void performAntiAction();

    protected:

    private:
        std::vector<ObjectValues> objectVals;

        int totalX = 0;
        int totalY = 0;
};

#endif // MOVEOBJECTCOMMAND_H
