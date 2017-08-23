#ifndef RESOURCETILECOVER_H
#define RESOURCETILECOVER_H

#include <wx/wx.h>

class ResourcePanel;
class ResourceTile;

//This class is a panel that covers the actual content on the resource browser.
//It's what the user clicks on to select a resource.
//This means that I didn't have to worry about which item in the icons list they clicked on (label, icon)
//I separated it into it's own class because this was the only way I could get it to work with the callbacks.

class ResourceTileCover : public wxPanel
{
    public:
        ResourceTileCover(ResourcePanel *resPanel, ResourceTile *parent);
        virtual ~ResourceTileCover();

        void mouseDown(wxMouseEvent &event);
        void mouseMoved(wxMouseEvent &event);
        void mouseUp(wxMouseEvent &event);

        void setId(int id);

    protected:

    private:
        ResourcePanel *resPanel;
        ResourceTile *parent;

        int id = 0;
};

#endif // RESOURCETILECOVER_H
