#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <wx/panel.h>

class MainFrame;
class wxAuiManager;
class wxBoxSizer;

class InspectorComponent;
class ObjectNameComponent;
class ObjectTransformComponent;
class NoSelectionComponent;

class ObjectInspector : public wxPanel
{
    public:
        ObjectInspector(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ObjectInspector();

        void setObjectInspectorVisability(bool visible);
        void addObjectComponent(InspectorComponent *component);

        void updateComponents();

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        NoSelectionComponent *noSelectionComponent;
        ObjectNameComponent *nameComponent;
        ObjectTransformComponent *transformComponent;
        wxBoxSizer *mainSizer;

        void singleSelection();
        void noSelection();

        bool inspectorVisible = false;
};

#endif // OBJECTINSPECTOR_H
