#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <wx/wx.h>
#include <Ogre.h>
#include "../Command.h"
#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

class HierarchyTree;

class AddObjectCommand : public Command
{
    public:
        AddObjectCommand(wxString path, HierarchyTree *tree);
        virtual ~AddObjectCommand();

    protected:

    private:
        HierarchyTree *tree;

        Object *object;

};

#endif // ADDOBJECTCOMMAND_H
