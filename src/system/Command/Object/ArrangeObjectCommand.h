#ifndef ARRANGEOBJECTCOMMAND_H
#define ARRANGEOBJECTCOMMAND_H

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "ObjectCommand.h"

struct ArrangeInformation : public ObjectInformation{
    wxTreeItemId originalParentId;
};

class ArrangeObjectCommand : public ObjectCommand
{
    public:
        ArrangeObjectCommand(HierarchyTree *tree, wxTreeItemId destination, wxArrayTreeItemIds items);
        virtual ~ArrangeObjectCommand();

        void performAction();
        void performAntiAction();

        void checkItems(wxTreeItemId oldId, wxTreeItemId newId);

    protected:

    private:
        wxTreeItemId destination;
        bool ran = false;

        std::vector<ArrangeInformation> objectInfo;
};

#endif // ARRANGEOBJECTCOMMAND_H
