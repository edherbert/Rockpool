#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include "../Command.h"

#include "../../../ui/Hierarchy/HierarchyTree.h"

struct ItemInformation{
    wxString text;
    int id;
    int parentId;

    int index;

    int originParentItem;
    int originItem;
    int newItem;
};

class HierarchyTree;

class ObjectCommand : public Command
{
    public:
        ObjectCommand(HierarchyTree *tree);
        virtual ~ObjectCommand();

    protected:
        HierarchyTree *tree;
        void searchItem(wxTreeItemId item, int parentId);

        int idCount = 0;

        std::vector<ItemInformation> itemInfo;

    private:
};

#endif // OBJECTCOMMAND_H
