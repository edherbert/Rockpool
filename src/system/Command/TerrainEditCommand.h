#ifndef TERRAINEDITCOMMAND_H
#define TERRAINEDITCOMMAND_H

#include "TerrainCommand.h"

class TerrainEditCommand : public TerrainCommand
{
    public:
        TerrainEditCommand(Terrain *terrain, int brushSize, int brushFlow);
        virtual ~TerrainEditCommand();

        void performAction();
        void performAntiAction();

        void pushIndividualRay(Ogre::TerrainGroup::RayResult individualRay);

    protected:

    private:
};

#endif // TERRAINEDITCOMMAND_H
