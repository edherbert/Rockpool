#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include <wx/treectrl.h>
#include "../Command.h"

struct ObjectInformation{
    wxString text;
    bool selected;

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

    private:
};

#endif // OBJECTCOMMAND_H
