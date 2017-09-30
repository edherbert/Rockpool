#ifndef POSITIONOBJECTCOMMAND_H
#define POSITIONOBJECTCOMMAND_H

#include "ObjectCommand.h"

#include <Ogre.h>

#include <vector>

class SelectionManager;
class Object;

enum ObjectAxis : unsigned int;

struct ObjectValues{
    Object *object;
    Ogre::Vector3 originPosition;
};

class PositionObjectCommand : public ObjectCommand
{
    public:
        PositionObjectCommand(SelectionManager *selectionManager, Ogre::Real position, ObjectAxis axis);
        virtual ~PositionObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        std::vector<ObjectValues> objectVals;

        ObjectAxis axis;
        Ogre::Real position;
};

#endif // POSITIONOBJECTCOMMAND_H
