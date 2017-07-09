#ifndef TERRAININFOLAYERBOX_H
#define TERRAININFOLAYERBOX_H

#include "TerrainInfoHandler.h"
#include <wx/wx.h>
#include <wx/statline.h>
#include "wxIDs.h"

class TerrainInfoHandler;

class TerrainInfoLayerBox : public wxPanel
{
    public:
        TerrainInfoLayerBox(wxWindow *parent, wxBoxSizer *parentSizer, TerrainInfoHandler *handler);
        virtual ~TerrainInfoLayerBox();

        bool isChecked();
        void setChecked(bool value);

        void setInfo(std::string name);
        std::string getInfo();

    protected:

    private:
        wxBoxSizer *parentSizer;
        TerrainInfoHandler *handler;

        bool checked = false;
        wxCheckBox *layerSelectedCheckBox;
        //wxStaticText *textureSrcText;
        wxTextCtrl *textureSrcText;

        void layerChecked(wxCommandEvent &event);
};

#endif // TERRAININFOLAYERBOX_H
