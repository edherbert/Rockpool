#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <vector>
#include <OgreVector3.h>

class Map;
class Object;

class SelectionManager
{
    public:
        SelectionManager(Map *map);
        virtual ~SelectionManager();

        void updateCurrentSelection();

        void setSelectionPosition(const Ogre::Vector3 &position);
        Ogre::Vector3 getSelectionCentrePosition();

    protected:

    private:
        Map *map;

        void calculateSelectionCentrePosition();

        std::vector<Object*> currentSelection;
        Ogre::Vector3 selectionCentrePosition;
};

#endif // SELECTIONMANAGER_H