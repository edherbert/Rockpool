#ifndef RESOURCETILE_H
#define RESOURCETILE_H

#include <wx/wx.h>
#include <wx/statbmp.h>

class ResourcePanel;
class ResourceTileCover;

class ResourceTile : public wxPanel
{
    public:
        ResourceTile(wxWindow *parent, ResourcePanel *resPanel, wxBitmap *defaultBitmap);
        virtual ~ResourceTile();

        void setLabel(const wxString &l);

        wxString getLabel();
        wxString getValue();

        void setSize(int width, int height);
        void setPosition(int x, int y);

        wxSize getSize();

        void setId(int id);
        int getId();

        void selectTile();
        void deSelectTile();

    protected:

    private:
        ResourcePanel *resPanel;
        wxWindow *parent;
        ResourceTileCover *cover;

        wxBitmap *defaultBitmap;

        int id = 0;

        wxStaticText *label;
        wxString currentValue = "";
};

#endif // RESOURCETILE_H
