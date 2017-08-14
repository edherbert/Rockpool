#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include <wx/treectrl.h>
#include "../Command.h"

struct ObjectInformation{
    wxString text;
    wxTreeItemId id;
    wxTreeItemId parentId;
    bool selected;
};

class HierarchyTree;

class ObjectCommand : public Command
{
    public:
        ObjectCommand(HierarchyTree *tree);
        virtual ~ObjectCommand();

        virtual void checkItems(wxTreeItemId oldId, wxTreeItemId newId);

    protected:
        HierarchyTree *tree;

    private:
};

#endif // OBJECTCOMMAND_H
