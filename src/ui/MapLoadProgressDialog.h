#ifndef MAPLOADPROGRESSDIALOG_H
#define MAPLOADPROGRESSDIALOG_H

#include <wx/wx.h>
#include "MainFrame.h"

class MainFrame;

class MapLoadProgressDialog : public wxDialog
{
    public:
        MapLoadProgressDialog(wxWindow *parent);
        virtual ~MapLoadProgressDialog();

        void setText(wxString text);
        void setValue(int ammount);
        void addValue(int ammount);

    protected:

    private:
        wxStaticText *progressText;
        wxGauge *progressGauge;

        int progressCount = 0;
};

#endif // MAPLOADPROGRESSDIALOG_H
