#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "../../map/Main.h"
#include "../MainFrame.h"
#include "../wxIDs.h"
#include "MapLoadProgressDialog.h"

class MainFrame;
class Main;

class NewMapDialog : public wxDialog
{
    public:
        NewMapDialog(MainFrame *parent, Main *main);
        virtual ~NewMapDialog();

    protected:

    private:
        void OKPressed(wxCommandEvent& WXUNUSED(event));
        void CancelPressed(wxCommandEvent& WXUNUSED(event));

        MainFrame *parent;
        Main *main;

        wxTextCtrl *mapNameControl;
        wxSpinCtrl *mapWidthSpin;
        wxSpinCtrl *mapHeightSpin;

        wxComboBox *vertexCountBox;
        wxSpinCtrl *terrainSizeSpin;
        wxSpinCtrl *terrainHeightSpin;
};

#endif // NEWMAPDIALOG_H
