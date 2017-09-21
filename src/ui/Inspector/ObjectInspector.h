#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <wx/panel.h>

class MainFrame;
class wxAuiManager;
class wxBoxSizer;

class InspectorComponent;
class ObjectNameComponent;
class ObjectTransformComponent;

class ObjectInspector : public wxPanel
{
    public:
        ObjectInspector(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ObjectInspector();

        void setObjectInspectorVisability(bool visible);

        void addObjectComponent(InspectorComponent *component);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        ObjectNameComponent *nameComponent;
        ObjectTransformComponent *transformComponent;

        wxBoxSizer *mainSizer;

        bool inspectorVisible = false;
};

#endif // OBJECTINSPECTOR_H
