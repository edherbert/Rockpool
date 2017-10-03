#ifndef SCALEOBJECTCOMMAND_H
#define SCALEOBJECTCOMMAND_H

#include <Ogre.h>

#include <vector>

class SelectionManager;
class Object;
class HierarchyTree;

enum ObjectAxis : unsigned int;

struct ObjectValues{
    Object *object;
    Ogre::Vector3 originScale;
};

class ScaleObjectCommand
{
    public:
        ScaleObjectCommand::ScaleObjectCommand(SelectionManager *SelectionManager, HierarchyTree *hierarchyTree, Ogre::Real scale, ObjectAxis axis);
        virtual ~ScaleObjectCommand();

    protected:

    private:
        std::vector<ObjectValues> objectVals;

        ObjectAxis axis;
        Ogre::Real position;
};

#endif // SCALEOBJECTCOMMAND_H
