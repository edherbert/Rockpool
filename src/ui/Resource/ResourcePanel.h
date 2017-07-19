#ifndef RESOURCEPANEL_H
#define RESOURCEPANEL_H

#include <wx/wx.h>
#include "ResourceTile.h"
#include "../../system/ResourceManager.h"

class ResourceManager;
class ResourceTile;

class ResourcePanel : public wxPanel
{
    public:
        ResourcePanel(wxWindow *parent, ResourceManager *resManager);
        virtual ~ResourcePanel();

        void updateTiles();
        void layoutTiles();

        void onResize(wxSizeEvent &event);
        void selectTile(int x, int y);

        ResourceTile* getCurrentTile();

    protected:

    private:
        wxWindow *parent;
        ResourceManager *resManager;

        int width, height;

        wxBitmap *defaultBitmap;

        ResourceTile *currentTile = 0;

        std::vector<ResourceTile*>tiles;
};

#endif // RESOURCEPANEL_H
