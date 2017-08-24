#ifndef RESOURCEDRAGPOPUP_H
#define RESOURCEDRAGPOPUP_H

#include <wx/popupwin.h>

class HierarchyTree;

class ResourceDragPopup : public wxPopupWindow
{
    public:
        ResourceDragPopup(HierarchyTree *tree);
        virtual ~ResourceDragPopup();

        void updatePopup();

    protected:

    private:
        HierarchyTree *tree;
};

#endif // RESOURCEDRAGPOPUP_H
