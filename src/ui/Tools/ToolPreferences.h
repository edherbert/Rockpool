#ifndef TOOLPREFERENCES_H
#define TOOLPREFERENCES_H

#include <wx/wx.h>
#include "../wxIDs.h"

class ToolPreferences : public wxPanel
{
    public:
        ToolPreferences(wxWindow *parentPanel);
        virtual ~ToolPreferences();

        void show(bool val);
        int getId();

    protected:
        wxWindow *parentPanel;
        //wxPanel *basePanel;

        wxBoxSizer *parentPanelSizer;

        int id = 0;

    private:
};

#endif // TOOLPREFERENCES_H
