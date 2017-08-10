#ifndef HIERARCHYRIGHTCLICKMENU_H
#define HIERARCHYRIGHTCLICKMENU_H

#include <wx/wx.h>

class HierarchyRightClickMenu : public wxMenu
{
    public:
        HierarchyRightClickMenu(wxWindow *parent, wxPoint location);
        virtual ~HierarchyRightClickMenu();

        void popup();

    protected:

    private:
        wxWindow *parent;
        wxPoint location;
};

#endif // HIERARCHYRIGHTCLICKMENU_H
