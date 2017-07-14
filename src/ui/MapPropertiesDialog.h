#ifndef MAPPROPERTIESDIALOG_H
#define MAPPROPERTIESDIALOG_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listbox.h>

#include "wxIDs.h"

class MapPropertiesDialog : public wxDialog
{
    public:
        MapPropertiesDialog(wxWindow *parent);
        virtual ~MapPropertiesDialog();

        void resourcesAddLocation(wxCommandEvent &event);
        void resourcesEditLocation(wxCommandEvent &event);
        void resourcesDeleteLocation(wxCommandEvent &event);

    protected:

    private:
        wxListBox *list;
};

#endif // MAPPROPERTIESDIALOG_H
