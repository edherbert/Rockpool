#ifndef TERRAININFOLAYERBOX_H
#define TERRAININFOLAYERBOX_H

#include "TerrainInfoHandler.h"

#include <wx/wx.h>
#include <wx/statline.h>

class TerrainInfoHandler;
class MainFrame;

class TerrainInfoLayerBox : public wxPanel
{
    public:
        TerrainInfoLayerBox(wxWindow *parent, MainFrame *mainFrame, wxBoxSizer *parentSizer, TerrainInfoHandler *handler);
        virtual ~TerrainInfoLayerBox();

        bool isChecked();
        void setChecked(bool value);

        void setInfo(const std::string &name);
        std::string getInfo();

    protected:

    private:
        wxBoxSizer *parentSizer;
        TerrainInfoHandler *handler;
        MainFrame *mainFrame;

        bool checked = false;
        wxCheckBox *layerSelectedCheckBox;

        wxStaticText *textureSrcText;
        //wxTextCtrl *textureSrcText;
        wxButton *textureSrcButton;

        void layerChecked(wxCommandEvent &event);
        void imageSelectButtonPressed(wxCommandEvent &event);
};

#endif // TERRAININFOLAYERBOX_H
