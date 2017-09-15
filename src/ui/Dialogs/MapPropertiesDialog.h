#ifndef MAPPROPERTIESDIALOG_H
#define MAPPROPERTIESDIALOG_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listbox.h>

#include <wx/filename.h>

#include "../MainFrame.h"

class MainFrame;

class MapPropertiesDialog : public wxDialog
{
    public:
        MapPropertiesDialog(MainFrame *mainFrame, wxWindow *parent);
        virtual ~MapPropertiesDialog();

        void doubleClickResourceList(wxCommandEvent &event);

        MainFrame* getMainFrame();

    protected:

    private:
        MainFrame *mainFrame;

        wxListBox *resourceLocationsList;
        wxListBox *skyBoxList;

        void setupMapProperties(wxPanel *parent);
        void setupResourceLocationProperties(wxPanel *parent);
        void setupSkyBoxProperties(wxPanel *parent);


        void resourcesAddLocation(wxCommandEvent &event);
        void resourcesEditLocationCallback(wxCommandEvent &event);
        void resourcesDeleteLocation(wxCommandEvent &event);
        void resourcesEditLocation();

        void addSkybox(wxCommandEvent &event);
        void editSkybox(wxCommandEvent &event);
        void deletekybox(wxCommandEvent &event);
};

#endif // MAPPROPERTIESDIALOG_H
