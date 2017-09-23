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

        void updateObjectLabel();
        void enterPressed(wxCommandEvent &event);
        void focusLost(wxFocusEvent &event);
};

#endif // OBJECTNAMECOMPONENT_H
