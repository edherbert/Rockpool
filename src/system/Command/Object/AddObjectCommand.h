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
        AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem = 0);
        virtual ~AddObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        HierarchyTree *tree;
        Object *object;
        wxTreeItemId parentItem;

};

#endif // ADDOBJECTCOMMAND_H
