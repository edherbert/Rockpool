#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include "ObjectCommand.h"

class Object;

enum PrimativeIds{
    PrimativeEmpty,
    PrimativeCube,
    PrimativeSphere,
    PrimativeCone,
    PrimativePlane
};

class AddObjectCommand : public ObjectCommand
{
    public:
        AddObjectCommand(const wxString &name, const wxString &path, HierarchyTree *tree, int parentItem = -1);
        AddObjectCommand(PrimativeIds primId, HierarchyTree *tree, int parentItem = -1);
        virtual ~AddObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        Object *object;

        int parentItem;
        int addedItem;

        wxString path;
        wxString name;

        int index = 0;

        void setup();

        bool ran = false;
};

#endif // ADDOBJECTCOMMAND_H
