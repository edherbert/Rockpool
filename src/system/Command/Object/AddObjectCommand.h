#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <wx/wx.h>
#include <Ogre.h>
#include "../Command.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

class AddObjectCommand : public Command
{
    public:
        AddObjectCommand(wxString path, Ogre::SceneManager *sceneManager, HierarchyTree *tree);
        virtual ~AddObjectCommand();

    protected:

    private:
        Ogre::SceneManager *sceneManager;
        HierarchyTree *tree;

        Object *object;

};

#endif // ADDOBJECTCOMMAND_H
