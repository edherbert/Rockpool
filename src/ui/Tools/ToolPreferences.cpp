#include "ToolPreferences.h"

ToolPreferences::ToolPreferences(wxWindow *parentPanel) : wxPanel(parentPanel){
    this->parentPanel = parentPanel;

    parentPanelSizer = new wxBoxSizer(wxVERTICAL);

    parentPanelSizer->Add(this, 1, wxEXPAND | wxALL);

    show(false);
}

ToolPreferences::~ToolPreferences(){

}

void ToolPreferences::show(bool val){
    this->Show(val);
    if(val){
        parentPanel->SetSizer(parentPanelSizer, false);
        parentPanel->Layout();
    }
}

int ToolPreferences::getId(){
    return id;
}
