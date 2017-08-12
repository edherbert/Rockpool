#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include <wx/treectrl.h>
#include "../Command.h"

class HierarchyTree;

class ObjectCommand : public Command
{
    public:
        ObjectCommand(HierarchyTree *tree, wxTreeItemId parentItem = 0);
        virtual ~ObjectCommand();

        void checkParent(wxTreeItemId oldId, wxTreeItemId newId);

    protected:
        wxTreeItemId parentItem;
        HierarchyTree *tree;

    private:
};

#endif // OBJECTCOMMAND_H
