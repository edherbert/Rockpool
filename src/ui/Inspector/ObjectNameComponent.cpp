#include "ObjectNameComponent.h"

#include <wx/sizer.h>
#include <wx/textctrl.h>

ObjectNameComponent::ObjectNameComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    //SetBackgroundColour(wxColour("#0000FF"));

    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    nameTextBox = new wxTextCtrl(this, wxID_ANY);

    mainSizer->Add(nameTextBox, 0, wxEXPAND | wxALL, 10);
}

ObjectNameComponent::~ObjectNameComponent(){

}
