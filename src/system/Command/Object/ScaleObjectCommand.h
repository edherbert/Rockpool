#ifndef SCALEOBJECTCOMMAND_H
#define SCALEOBJECTCOMMAND_H

#include "ObjectCommand.h"

#include <Ogre.h>

#include <vector>

class SelectionManager;
class Object;
class HierarchyTree;

enum ObjectAxis : unsigned int;

struct ObjectScaleValues{
    Object *object;
    Ogre::Vector3 originScale;
};

class ScaleObjectCommand : public ObjectCommand
{
    public:
        ScaleObjectCommand(SelectionManager *selectionManager, HierarchyTree *hierarchyTree, Ogre::Real scale, ObjectAxis axis);
        virtual ~ScaleObjectCommand();

        virtual void performAction();
        virtual void performAntiAction();

    protected:

    private:
        std::vector<ObjectScaleValues> objectVals;

        ObjectAxis axis;
        Ogre::Real scale;
};

#endif // SCALEOBJECTCOMMAND_H
