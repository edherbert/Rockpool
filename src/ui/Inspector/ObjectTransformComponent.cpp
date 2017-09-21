#include "ObjectTransformComponent.h"

#include "NumberTextCtrl.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>

ObjectTransformComponent::ObjectTransformComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    //SetBackgroundColour(wxColour("#0000FF"));
    this->inspector = inspector;

    mainSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Transform");
    SetSizer(mainSizer);

    setupPosition("Position:");
    setupPosition("Scale:");
    setupPosition("Rotation:");
}

ObjectTransformComponent::~ObjectTransformComponent(){

}

void ObjectTransformComponent::setupPosition(const wxString &title){
    wxStaticText *titleText = new wxStaticText(this, 0, title);
    titleText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxFlexGridSizer *test = new wxFlexGridSizer(1, 6, 1, 1);

    wxStaticText *xText = new wxStaticText(this, wxID_ANY, "X");
    NumberTextCtrl *xCtrl = new NumberTextCtrl(this, wxID_ANY);
    wxStaticText *yText = new wxStaticText(this, wxID_ANY, "Y");
    NumberTextCtrl *yCtrl = new NumberTextCtrl(this, wxID_ANY);
    wxStaticText *zText = new wxStaticText(this, wxID_ANY, "Z");
    NumberTextCtrl *zCtrl = new NumberTextCtrl(this, wxID_ANY);

    xCtrl->SetMinSize(wxSize(10, 30));
    yCtrl->SetMinSize(wxSize(10, 30));
    zCtrl->SetMinSize(wxSize(10, 30));

    test->Add(xText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    test->Add(xCtrl, 1, wxEXPAND);
    test->Add(yText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    test->Add(yCtrl, 1, wxEXPAND);
    test->Add(zText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    test->Add(zCtrl, 1, wxEXPAND);

    test->AddGrowableCol(1, 1);
    test->AddGrowableCol(3, 1);
    test->AddGrowableCol(5, 1);

    mainSizer->Add(titleText, 0, wxEXPAND | wxALL, 2);
    mainSizer->Add(test, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
}
