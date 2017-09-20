#ifndef OBJECTNAMECOMPONENT_H
#define OBJECTNAMECOMPONENT_H

#include "InspectorComponent.h"

class wxTextCtrl;

class ObjectNameComponent : public InspectorComponent
{
    public:
        ObjectNameComponent(ObjectInspector *inspector);
        virtual ~ObjectNameComponent();

    protected:

    private:
        wxTextCtrl *nameTextBox;
};

#endif // OBJECTNAMECOMPONENT_H
