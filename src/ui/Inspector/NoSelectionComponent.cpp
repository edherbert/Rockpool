#include "NoSelectionComponent.h"

#include "ObjectInspector.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

NoSelectionComponent::NoSelectionComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(mainSizer);

    wxStaticText *noSelectionText = new wxStaticText(this, wxID_ANY, "No objects are selected.");

    //I've done it with panels because the centre align flag didn't want to work.
    mainSizer->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND);
    mainSizer->Add(noSelectionText, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(new wxPanel(this, wxID_ANY), 1, wxEXPAND);
}

NoSelectionComponent::~NoSelectionComponent(){

}
