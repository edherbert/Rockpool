#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "ObjectCommand.h"

class Object;

class AddObjectCommand : public ObjectCommand
{
    public:
        AddObjectCommand(wxString path, HierarchyTree *tree, wxTreeItemId parentItem = 0);
        virtual ~AddObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        Object *object;

        wxString path;
        wxTreeItemId addedItem;
};

#endif // ADDOBJECTCOMMAND_H
