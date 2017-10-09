#include "ObjectTransformComponent.h"

#include "OgreVector3.h"
#include "OgreString.h"
#include "../wxIDs.h"

#include "../../map/SelectionManager.h"
#include "../../map/Object/Object.h"
#include "ObjectTransformNumberCtrl.h"
#include "ObjectInspector.h"
#include "../../map/Map.h"

#include "../MainFrame.h"
#include "../GLCanvas.h"

#include <wx/sizer.h>
#include <wx/stattext.h>

ObjectTransformComponent::ObjectTransformComponent(ObjectInspector *inspector) : InspectorComponent(inspector){
    //SetBackgroundColour(wxColour("#0000FF"));

    mainSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Transform");
    SetSizer(mainSizer);

    int positionIds[3] = {TRANSFORM_COMPONENT_POSITION_X, TRANSFORM_COMPONENT_POSITION_Y, TRANSFORM_COMPONENT_POSITION_Z};
    int scaleIds[3] = {TRANSFORM_COMPONENT_SCALE_X, TRANSFORM_COMPONENT_SCALE_Y, TRANSFORM_COMPONENT_SCALE_Z};
    int rotationIds[3] = {TRANSFORM_COMPONENT_ROTATION_X, TRANSFORM_COMPONENT_ROTATION_Y, TRANSFORM_COMPONENT_ROTATION_Z};

    setupInputs("Position:", positionCtrls, positionIds);
    setupInputs("Scale:", scaleCtrls, scaleIds);
    setupInputs("Rotation:", rotationCtrls, rotationIds);
}

ObjectTransformComponent::~ObjectTransformComponent(){

}

void ObjectTransformComponent::setupInputs(const wxString &title, ObjectTransformNumberCtrl* ctrls[3], int ids[3]){
    wxStaticText *titleText = new wxStaticText(this, 0, title);
    titleText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxFlexGridSizer *gridSizer = new wxFlexGridSizer(1, 6, 1, 1);

    wxStaticText *xText = new wxStaticText(this, wxID_ANY, "X");
    ObjectTransformNumberCtrl *xCtrl = new ObjectTransformNumberCtrl(this, ids[0], ObjectAxisX);
    wxStaticText *yText = new wxStaticText(this, wxID_ANY, "Y");
    ObjectTransformNumberCtrl *yCtrl = new ObjectTransformNumberCtrl(this, ids[1], ObjectAxisY);
    wxStaticText *zText = new wxStaticText(this, wxID_ANY, "Z");
    ObjectTransformNumberCtrl *zCtrl = new ObjectTransformNumberCtrl(this, ids[2], ObjectAxisZ);

    ctrls[0] = xCtrl;
    ctrls[1] = yCtrl;
    ctrls[2] = zCtrl;

    xCtrl->SetMinSize(wxSize(10, 30));
    yCtrl->SetMinSize(wxSize(10, 30));
    zCtrl->SetMinSize(wxSize(10, 30));

    gridSizer->Add(xText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    gridSizer->Add(xCtrl, 1, wxEXPAND);
    gridSizer->Add(yText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    gridSizer->Add(yCtrl, 1, wxEXPAND);
    gridSizer->Add(zText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 2);
    gridSizer->Add(zCtrl, 1, wxEXPAND);

    gridSizer->AddGrowableCol(1, 1);
    gridSizer->AddGrowableCol(3, 1);
    gridSizer->AddGrowableCol(5, 1);

    mainSizer->Add(titleText, 0, wxEXPAND | wxALL, 2);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    Connect(wxEVT_TEXT_ENTER, wxCommandEventHandler(ObjectTransformComponent::checkEnter));
}

void ObjectTransformComponent::updateInformation(){
    Object* firstObject = inspector->getMap()->getSelectionManager()->getFirstObject();
    Ogre::Vector3 position = firstObject->getPosition();
    Ogre::Vector3 scale = firstObject->getScale();

    //Bools to identify which axises contain different values
    std::array<bool, 3> positionVals = inspector->getMap()->getSelectionManager()->getPositionDifference();
    std::array<bool, 3> scaleVals = inspector->getMap()->getSelectionManager()->getScaleDifference();

    for(int i = 0; i < 3; i++){
        if(positionVals[i]){
            positionCtrls[i]->SetValue("...");
        }else{
            positionCtrls[i]->SetValue(Ogre::StringConverter::toString(position[i]));
        }

        if(scaleVals[i]){
            scaleCtrls[i]->SetValue("...");
        }else{
            scaleCtrls[i]->SetValue(Ogre::StringConverter::toString(scale[i]));
        }
    }
}

void ObjectTransformComponent::pushInformation(ObjectTransformNumberCtrl* ctrl){
    ObjectAxis axis;

    //Clean this up later
    if(ctrl->GetId() >= 665 && ctrl->GetId() <= 667){
        inspector->getMap()->getSelectionManager()->setSelectionPosition(ctrl->getIntValue(), ctrl->getAxis());
    }
    if(ctrl->GetId() >= 668 && ctrl->GetId() <= 670){
        inspector->getMap()->getSelectionManager()->setSelectionScale(ctrl->getIntValue(), ctrl->getAxis());
    }

    inspector->getMainFrame()->getCanvas()->renderFrame();
}

void ObjectTransformComponent::checkEnter(wxCommandEvent &event){
    pushInformation((ObjectTransformNumberCtrl*)event.GetEventObject());
}
