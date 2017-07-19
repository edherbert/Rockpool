#ifndef TERRAINLAYERRESOURCEDIALOG_H
#define TERRAINLAYERRESOURCEDIALOG_H

#include <wx/wx.h>
#include "../../system/ResourceManager.h"
#include "../Resource/ResourcePanel.h"

class ResourceManager;
class ResourcePanel;

class TerrainLayerResourceDialog : public wxDialog
{
    public:
        TerrainLayerResourceDialog(wxWindow *parent, ResourceManager *resManager);
        virtual ~TerrainLayerResourceDialog();

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

#endif // TERRAINLAYERRESOURCEDIALOG_H
