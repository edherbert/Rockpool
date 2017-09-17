#ifndef MAPPROPERTIESSKYBOXDIALOG_H
#define MAPPROPERTIESSKYBOXDIALOG_H

#include <wx/dialog.h>
#include "../wxIDs.h"

class wxWindow;
class MapPropertiesDialog;
class SkyBox;
class wxStaticText;
class wxTextCtrl;

class MapPropertiesSkyBoxDialog : public wxDialog
{
    public:
        MapPropertiesSkyBoxDialog(MapPropertiesDialog *parentDialog, SkyBox *editedSkyBox = 0);
        virtual ~MapPropertiesSkyBoxDialog();

    protected:

    private:
        MapPropertiesDialog *parentDialog;
        SkyBox *tempSkyBox;
        SkyBox *editedSkyBox;
        wxTextCtrl *skyBoxNameTextCtrl;

        void cancelButtonPressed(wxCommandEvent &event);
        void imageButtonPressed(wxCommandEvent &event);
        void okButtonPressed(wxCommandEvent &event);

        int buttonIDs[6] = {DIALOG_SKYBOX_ID_FRONT, DIALOG_SKYBOX_ID_BACK, DIALOG_SKYBOX_ID_UP, DIALOG_SKYBOX_ID_DOWN, DIALOG_SKYBOX_ID_LEFT, DIALOG_SKYBOX_ID_RIGHT};

        //pointers to the widget that displays the path. This is so they can have their values set first.
        wxStaticText* pathStrings[6];

};

#endif // MAPPROPERTIESSKYBOXDIALOG_H
