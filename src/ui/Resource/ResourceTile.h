#ifndef RESOURCETILE_H
#define RESOURCETILE_H

#include <wx/wx.h>
#include <wx/statbmp.h>
#include "ResourcePanel.h"
#include "ResourceTileCover.h"

class ResourcePanel;
class ResourceTileCover;

class ResourceTile : public wxPanel
{
    public:
        ResourceTile(ResourcePanel *parent, wxBitmap *defaultBitmap);
        virtual ~ResourceTile();

        void setLabel(wxString l);

        wxString getLabel();
        wxString getValue();

        void setSize(int width, int height);
        void setPosition(int x, int y);

        void setId(int id);
        int getId();

        void selectTile();
        void deSelectTile();

    protected:

    private:
        ResourcePanel *parent;
        ResourceTileCover *cover;

        wxBitmap *defaultBitmap;

        int id = 0;

        wxStaticText *label;
        wxString currentValue = "";
};

#endif // RESOURCETILE_H
