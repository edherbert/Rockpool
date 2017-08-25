#ifndef RESOURCEDRAGPOPUP_H
#define RESOURCEDRAGPOPUP_H

#include <wx/popupwin.h>

class ResourcePanel;
class ResourceTile;

class ResourceDragPopup : public wxPopupWindow
{
    public:
        ResourceDragPopup(ResourcePanel *panel);
        virtual ~ResourceDragPopup();

        void update();

    protected:

    private:
        ResourcePanel *panel;
        ResourceTile *tile;
};

#endif // RESOURCEDRAGPOPUP_H
