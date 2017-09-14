#ifndef MAPPROPERTIESSKYBOXDIALOG_H
#define MAPPROPERTIESSKYBOXDIALOG_H

#include <wx/dialog.h>

class wxWindow;

class MapPropertiesSkyBoxDialog : public wxDialog
{
    public:
        MapPropertiesSkyBoxDialog(wxWindow *parent);
        virtual ~MapPropertiesSkyBoxDialog();

    protected:

    private:
        void cancelButtonPressed(wxCommandEvent &event);
};

#endif // MAPPROPERTIESSKYBOXDIALOG_H
