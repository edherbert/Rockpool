#ifndef HIERARCHYRIGHTCLICKNEW_H
#define HIERARCHYRIGHTCLICKNEW_H

#include <wx/wx.h>
#include "../wxIDs.h"

class HierarchyRightClickNew : public wxMenu
{
    public:
        HierarchyRightClickNew();
        virtual ~HierarchyRightClickNew();

    protected:

    private:
        void addCubeClick(wxCommandEvent &event);
};

#endif // HIERARCHYRIGHTCLICKNEW_H
