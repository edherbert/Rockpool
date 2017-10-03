#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <vector>
#include <OgreVector3.h>

class Map;
class Object;

enum ObjectAxis : unsigned int;

class SelectionManager
{
    public:
        SelectionManager(Map *map);
        virtual ~SelectionManager();

        void updateCurrentSelection();

        Ogre::Vector3 getSelectionCentrePosition();
        void setSelectionPosition(Ogre::Real position, ObjectAxis axis);
        void setSelectionScale(Ogre::Real scale, ObjectAxis axis);
        Object* getFirstObject();

        std::array<bool, 3> getPositionDifference();

        const std::vector<Object*>& getSelectionObjects();

    protected:

    private:
        Map *map;

        void calculateSelectionCentrePosition();

        std::vector<Object*> currentSelection;
        Ogre::Vector3 selectionCentrePosition;
};

#endif // SELECTIONMANAGER_H
