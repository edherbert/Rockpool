#include "ObjectNameComponent.h"

#include <wx/sizer.h>
#include <wx/textctrl.h>

#include "../../map/Object/Object.h"

ObjectNameComponent::ObjectNameComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    nameTextBox = new wxTextCtrl(this, wxID_ANY);

    mainSizer->Add(nameTextBox, 0, wxEXPAND | wxALL, 10);
}

ObjectNameComponent::~ObjectNameComponent(){

}

void ObjectNameComponent::updateInformation(Object *object){
    nameTextBox->SetValue("Hello");
    //The values from the object hierarchy will be needed
}
