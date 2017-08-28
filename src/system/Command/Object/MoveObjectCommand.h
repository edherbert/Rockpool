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

        void update(const Ogre::Vector3 &current, TargetAxis axis);

        void performAction();
        void performAntiAction();

    protected:

    private:
        std::vector<ObjectValues> objectVals;

        Ogre::Vector3 previous;
        Ogre::Vector3 delta;
        bool foundInitial = false;
};

#endif // MOVEOBJECTCOMMAND_H
