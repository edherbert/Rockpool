#ifndef OBJECTHIERARCHY_H
#define OBJECTHIERARCHY_H

#include "../MainFrame.h"
#include "HierarchyTree.h"

class MainFrame;

class ObjectHierarchy : public wxPanel
{
    public:
        ObjectHierarchy(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ObjectHierarchy();

        void setObjectHierarchyVisible(bool visible);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;

        bool hierarchyVisible = false;
};

#endif // OBJECTHIERARCHY_H
