#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <wx/panel.h>

class MainFrame;
class wxAuiManager;

class ObjectInspector : public wxPanel
{
    public:
        ObjectInspector(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ObjectInspector();

        void setObjectInspectorVisability(bool visible);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        bool inspectorVisible = false;
};

#endif // OBJECTINSPECTOR_H
