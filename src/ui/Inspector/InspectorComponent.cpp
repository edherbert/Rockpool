#include "InspectorComponent.h"

#include "ObjectInspector.h"

#include <wx/button.h>
#include <wx/sizer.h>

InspectorComponent::InspectorComponent(ObjectInspector *inspector) : wxPanel(inspector){
    this->inspector = inspector;
}

InspectorComponent::~InspectorComponent(){

}
