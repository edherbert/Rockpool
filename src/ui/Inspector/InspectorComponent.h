#ifndef INSPECTORCOMPONENT_H
#define INSPECTORCOMPONENT_H

#include <wx/panel.h>

class ObjectInspector;
class wxBoxSizer;

class InspectorComponent : public wxPanel
{
    public:
        InspectorComponent(ObjectInspector *inspector);
        virtual ~InspectorComponent();

    protected:
        ObjectInspector *inspector;
        wxBoxSizer *mainSizer;

    private:
};

#endif // INSPECTORCOMPONENT_H
