#ifndef OBJECTTRANSFORMCOMPONENT_H
#define OBJECTTRANSFORMCOMPONENT_H

#include "InspectorComponent.h"

class ObjectInspector;
class NumberTextCtrl;
class Object;
class SelectionManager;

class ObjectTransformComponent : public InspectorComponent
{
    public:
        ObjectTransformComponent(ObjectInspector *inspector);
        virtual ~ObjectTransformComponent();

        void updateInformation(SelectionManager *selectionManager);

        void specialKeyPressed();
        void test(wxCommandEvent &event);
        void doChar(wxKeyEvent &event);

    protected:

    private:
        void setupInputs(const wxString &title, NumberTextCtrl* ctrls[3]);

        NumberTextCtrl* positionCtrls[3];
        NumberTextCtrl* scaleCtrls[3];
        NumberTextCtrl* rotationCtrls[3];
};

#endif // OBJECTTRANSFORMCOMPONENT_H
