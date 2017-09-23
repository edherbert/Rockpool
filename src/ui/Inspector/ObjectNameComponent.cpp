#include "ObjectNameComponent.h"

#include <wx/sizer.h>
#include <wx/textctrl.h>

#include "../wxIDs.h"

#include "../../map/Object/Object.h"
#include "../MainFrame.h"
#include "ObjectInspector.h"
#include "../Hierarchy/ObjectHierarchy.h"
#include "../Hierarchy/HierarchyTree.h"

ObjectNameComponent::ObjectNameComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    nameTextBox = new wxTextCtrl(this, NAME_COMPONENT_BOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    mainSizer->Add(nameTextBox, 0, wxEXPAND | wxALL, 10);

    Connect(wxEVT_TEXT_ENTER, wxCommandEventHandler(ObjectNameComponent::enterPressed));
}

ObjectNameComponent::~ObjectNameComponent(){

}

void ObjectNameComponent::updateInformation(Object *object){
    nameTextBox->SetValue(inspector->getMainFrame()->getObjectHierarchy()->getTree()->getFirstSelectionString());
}

void ObjectNameComponent::updateObjectLabel(){
    if(nameTextBox->GetValue() == wxEmptyString) return;
    inspector->getMainFrame()->getObjectHierarchy()->getTree()->setFirstSelectionString(nameTextBox->GetValue());
}

void ObjectNameComponent::enterPressed(wxCommandEvent &event){
    updateObjectLabel();
}

void ObjectNameComponent::focusLost(wxFocusEvent &event){
    std::cout << "focus lost" << std::endl;
}
