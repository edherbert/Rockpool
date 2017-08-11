#ifndef OBJECTHIERARCHY_H
#define OBJECTHIERARCHY_H

#include "../MainFrame.h"
#include "HierarchyTree.h"

class MainFrame;
class HierarchyTree;

class ObjectHierarchy : public wxPanel
{
    public:
        ObjectHierarchy(MainFrame *mainFrame, wxAuiManager *auiManager);
        virtual ~ObjectHierarchy();

        void setObjectHierarchyVisible(bool visible);
        void setMap(Map *map);

    protected:

    private:
        MainFrame *mainFrame;
        wxAuiManager *auiManager;
        HierarchyTree *tree;

        bool hierarchyVisible = false;
};

#endif // OBJECTHIERARCHY_H
