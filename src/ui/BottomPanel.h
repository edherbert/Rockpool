#ifndef BOTTOMPANEL_H
#define BOTTOMPANEL_H

#include <wx/wx.h>
#include <wx/tglbtn.h>

class BottomPanel
{
    public:
        BottomPanel(wxPanel *parentPanel);
        virtual ~BottomPanel();

    protected:

    private:
        wxPanel *parentPanel;
        wxBoxSizer *contentHorizontal;
};

#endif // BOTTOMPANEL_H
