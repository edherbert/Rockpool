#ifndef OBJECTTRANSFORMCOMPONENT_H
#define OBJECTTRANSFORMCOMPONENT_H

#include "InspectorComponent.h"

class ObjectInspector;
class ObjectTransformNumberCtrl;
class Object;
class SelectionManager;

class ObjectTransformComponent : public InspectorComponent
{
    public:
        ObjectTransformComponent(ObjectInspector *inspector);
        virtual ~ObjectTransformComponent();

        void updateInformation();

        void checkEnter(wxCommandEvent &event);
        void pushInformation(ObjectTransformNumberCtrl* ctrl);

    protected:

    private:
        void setupInputs(const wxString &title, ObjectTransformNumberCtrl* ctrls[3], int ids[3]);

        ObjectTransformNumberCtrl* positionCtrls[3];
        ObjectTransformNumberCtrl* scaleCtrls[3];
        ObjectTransformNumberCtrl* rotationCtrls[3];
};

#endif // OBJECTTRANSFORMCOMPONENT_H
