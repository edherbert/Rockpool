#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include "../../../map/Object/Object.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "ObjectCommand.h"

class Object;

class AddObjectCommand : public ObjectCommand
{
    public:
        AddObjectCommand(wxString path, HierarchyTree *tree, int parentItem = -1);
        virtual ~AddObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        Object *object;
        //wxTreeItemId parentItem;
        int parentItem;

        wxString path;
        //wxTreeItemId addedItem;
        int addedItem;

        int index = 0;

        bool ran = false;
};

#endif // ADDOBJECTCOMMAND_H
