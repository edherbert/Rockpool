#include "MultipleSelectionTitleComponent.h"

#include "ObjectInspector.h"
#include <wx/stattext.h>
#include <wx/sizer.h>

MultipleSelectionTitleComponent::MultipleSelectionTitleComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    titleText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    titleText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    mainSizer->Add(titleText, 0, wxALL, 10);
}

MultipleSelectionTitleComponent::~MultipleSelectionTitleComponent(){

}

void MultipleSelectionTitleComponent::updateObjectCount(int objects){
    this->objectCount = objects;

    titleText->SetLabel(std::to_string(objectCount) + " objects selected");
}
