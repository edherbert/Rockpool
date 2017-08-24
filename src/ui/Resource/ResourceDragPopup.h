#ifndef RESOURCEDRAGPOPUP_H
#define RESOURCEDRAGPOPUP_H

#include <wx/popupwin.h>

class ResourcePanel;

class ResourceDragPopup : public wxPopupWindow
{
    public:
        ResourceDragPopup(ResourcePanel *panel);
        virtual ~ResourceDragPopup();

        void update();

    protected:

    private:
        ResourcePanel *panel;
};

#endif // RESOURCEDRAGPOPUP_H
