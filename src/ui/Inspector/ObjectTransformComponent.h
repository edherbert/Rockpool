#ifndef OBJECTTRANSFORMCOMPONENT_H
#define OBJECTTRANSFORMCOMPONENT_H

#include "InspectorComponent.h"

class ObjectInspector;

class ObjectTransformComponent : public InspectorComponent
{
    public:
        ObjectTransformComponent(ObjectInspector *inspector);
        virtual ~ObjectTransformComponent();

    protected:

    private:
        void setupPosition(const wxString &title);
};

#endif // OBJECTTRANSFORMCOMPONENT_H
