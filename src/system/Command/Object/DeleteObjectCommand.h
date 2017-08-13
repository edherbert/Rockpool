#ifndef DELETEOBJECTCOMMAND_H
#define DELETEOBJECTCOMMAND_H

#include "ObjectCommand.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

struct deleteObjectInformation{
    wxString text;
    wxTreeItemId id;
    wxTreeItemId parentId;
    bool selected;
};

class DeleteObjectCommand : public ObjectCommand
{
    public:
        DeleteObjectCommand(HierarchyTree *tree, wxArrayTreeItemIds items);
        virtual ~DeleteObjectCommand();

        void performAction();
        void performAntiAction();

        void checkItems(wxTreeItemId oldId, wxTreeItemId newId);

    protected:

    private:

        std::vector<deleteObjectInformation> objectInfo;
};

#endif // DELETEOBJECTCOMMAND_H
