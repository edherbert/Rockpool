#ifndef OBJECTNAMECOMPONENT_H
#define OBJECTNAMECOMPONENT_H

#include "InspectorComponent.h"

class wxTextCtrl;
class Object;

class ObjectNameComponent : public InspectorComponent
{
    public:
        ObjectNameComponent(ObjectInspector *inspector);
        virtual ~ObjectNameComponent();

        void updateInformation(Object *object);

    protected:

    private:
        wxTextCtrl *nameTextBox;
};

#endif // OBJECTNAMECOMPONENT_H
