#ifndef RESOURCEPANEL_H
#define RESOURCEPANEL_H

#include <wx/wx.h>
#include "ResourceTile.h"
#include "../../system/ResourceManager.h"

class ResourceManager;

class ResourcePanel : public wxPanel
{
    public:
        ResourcePanel(wxWindow *parent, ResourceManager *resManager);
        virtual ~ResourcePanel();

        void updateTiles();
        void layoutTiles();

        void onResize(wxSizeEvent &event);

    protected:

    private:
        wxWindow *parent;
        ResourceManager *resManager;

        std::vector<ResourceTile*>tiles;
};

#endif // RESOURCEPANEL_H
