#ifndef HIERARCHYOBJECTINFORMATION_H
#define HIERARCHYOBJECTINFORMATION_H

#include <wx/treebase.h>

class Object;

class HierarchyObjectInformation : public wxTreeItemData
{
    public:
        HierarchyObjectInformation(Object *object);
        virtual ~HierarchyObjectInformation();

        Object* getObject();

    protected:

    private:
        Object *object;
};

#endif // HIERARCHYOBJECTINFORMATION_H
