#ifndef MAPPROPERTIESDIALOG_H
#define MAPPROPERTIESDIALOG_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listbox.h>

#include <wx/filename.h>

#include "../MainFrame.h"

#include "../wxIDs.h"

class MainFrame;

class MapPropertiesDialog : public wxDialog
{
    public:
        MapPropertiesDialog(MainFrame *mainFrame, wxWindow *parent);
        virtual ~MapPropertiesDialog();

        void resourcesAddLocation(wxCommandEvent &event);
        void resourcesEditLocationCallback(wxCommandEvent &event);
        void resourcesDeleteLocation(wxCommandEvent &event);
        void resourcesEditLocation();

        void doubleClickResourceList(wxCommandEvent &event);

    protected:

    private:
        wxListBox *list;
        MainFrame *mainFrame;

        void setupMapProperties(wxPanel *parent);
};

#endif // MAPPROPERTIESDIALOG_H
