#ifndef MAPPROPERTIESSKYBOXDIALOG_H
#define MAPPROPERTIESSKYBOXDIALOG_H

#include <wx/dialog.h>
#include "../wxIDs.h"

class wxWindow;
class MapPropertiesDialog;

class MapPropertiesSkyBoxDialog : public wxDialog
{
    public:
        MapPropertiesSkyBoxDialog(MapPropertiesDialog *parentDialog);
        virtual ~MapPropertiesSkyBoxDialog();

    protected:

    private:
        MapPropertiesDialog *parentDialog;

        void cancelButtonPressed(wxCommandEvent &event);
        void imageButtonPressed(wxCommandEvent &event);

        int buttonIDs[6] = {DIALOG_SKYBOX_ID_FRONT, DIALOG_SKYBOX_ID_BACK, DIALOG_SKYBOX_ID_UP, DIALOG_SKYBOX_ID_DOWN, DIALOG_SKYBOX_ID_LEFT, DIALOG_SKYBOX_ID_RIGHT};
};

#endif // MAPPROPERTIESSKYBOXDIALOG_H
