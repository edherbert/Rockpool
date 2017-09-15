#ifndef RESOURCESELECTIONPOPUP_H
#define RESOURCESELECTIONPOPUP_H

#include <wx/wx.h>
#include "../../system/ResourceManager.h"
#include "../Resource/ResourcePanel.h"

class ResourceManager;
class ResourcePanel;
class MainFrame;

class ResourceSelectionPopup : public wxDialog
{
    public:
        ResourceSelectionPopup(wxWindow *parent, MainFrame *mainFrame, ResourceManager *resManager);
        virtual ~ResourceSelectionPopup();

        void cancelButtonPressed(wxCommandEvent &event);
        void selectButtonPressed(wxCommandEvent &event);

        wxString getValue();

    protected:

    private:
        wxWindow *parent;
        ResourceManager *resManager;

        wxString returnValue;

        ResourcePanel *resourcePanel;
};

#endif // RESOURCESELECTIONPOPUP_H
