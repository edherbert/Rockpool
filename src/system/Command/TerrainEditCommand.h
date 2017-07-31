#ifndef TERRAINEDITCOMMAND_H
#define TERRAINEDITCOMMAND_H

#include "TerrainCommand.h"
#include "../../ui/wxIDs.h"

class TerrainEditCommand : public TerrainCommand
{
    public:
        TerrainEditCommand(Terrain *terrain, Ogre::Terrain *terr, int toolId);
        virtual ~TerrainEditCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        int toolId;
};

#endif // TERRAINEDITCOMMAND_H
