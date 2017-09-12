#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include <wx/string.h>
#include <wx/treebase.h>

#include <vector>
#include <OgreVector3.h>

#include "../Command.h"

class HierarchyTree;
class Object;

struct ItemInformation{
    wxString text;
    int id;
    int parentId;

    Object *itemObject;

    int index;

    int originParentItem;
    int originItem;
    int newItem;
};

enum TargetAxis{
    TargetAxisX,
    TargetAxisY,
    TargetAxisZ,
    TargetAxisNone
};

class ObjectCommand : public Command
{
    public:
        ObjectCommand(HierarchyTree *tree);
        virtual ~ObjectCommand();

        virtual void update(const Ogre::Vector3 &current, TargetAxis axis);

    protected:
        HierarchyTree *tree;
        void searchItem(wxTreeItemId item, int parentId);

        int idCount = 0;

        std::vector<ItemInformation> itemInfo;

    private:
};

#endif // OBJECTCOMMAND_H
