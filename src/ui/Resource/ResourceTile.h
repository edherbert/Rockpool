#ifndef RESOURCETILE_H
#define RESOURCETILE_H

#include <wx/wx.h>
#include <wx/statbmp.h>

class ResourceTile : public wxPanel
{
    public:
        ResourceTile(wxWindow *parent);
        virtual ~ResourceTile();

        void setLabel(wxString l);

    protected:

    private:
        wxWindow *parent;

        wxStaticText *label;
};

#endif // RESOURCETILE_H
