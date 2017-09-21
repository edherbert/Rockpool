#ifndef NOSELECTIONCOMPONENT_H
#define NOSELECTIONCOMPONENT_H

#include "InspectorComponent.h"

class ObjectInspector;

class NoSelectionComponent : public InspectorComponent
{
    public:
        NoSelectionComponent(ObjectInspector *inspector);
        virtual ~NoSelectionComponent();

    protected:

    private:
};

#endif // NOSELECTIONCOMPONENT_H
