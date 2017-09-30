#include "ObjectTransformComponent.h"

#include "OgreVector3.h"
#include "OgreString.h"
#include "../wxIDs.h"

#include "../../map/SelectionManager.h"
#include "../../map/Object/Object.h"
#include "NumberTextCtrl.h"
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

void ObjectTransformComponent::setupInputs(const wxString &title, NumberTextCtrl* ctrls[3], int ids[3]){
    wxStaticText *titleText = new wxStaticText(this, 0, title);
    titleText->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxFlexGridSizer *gridSizer = new wxFlexGridSizer(1, 6, 1, 1);

    wxStaticText *xText = new wxStaticText(this, wxID_ANY, "X");
    NumberTextCtrl *xCtrl = new NumberTextCtrl(this, ids[0]);
    wxStaticText *yText = new wxStaticText(this, wxID_ANY, "Y");
    NumberTextCtrl *yCtrl = new NumberTextCtrl(this, ids[1]);
    wxStaticText *zText = new wxStaticText(this, wxID_ANY, "Z");
    NumberTextCtrl *zCtrl = new NumberTextCtrl(this, ids[2]);

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
    Ogre::Vector3 position = inspector->getMap()->getSelectionManager()->getSelectionCentrePosition();
    Ogre::Vector3 scale = Ogre::Vector3(1, 1, 1);

    std::array<bool, 3> vals = inspector->getMap()->getSelectionManager()->getPositionDifference();

    for(int i = 0; i < 3; i++){
        if(vals[i]){
            positionCtrls[i]->SetValue("...");
        }else{
            positionCtrls[i]->SetValue(Ogre::StringConverter::toString(position[i]));
        }

        scaleCtrls[i]->SetValue(Ogre::StringConverter::toString(scale[i]));
    }
}

void ObjectTransformComponent::pushInformation(NumberTextCtrl* ctrl){
    ObjectAxis axis;
    if(ctrl->GetId() == TRANSFORM_COMPONENT_POSITION_X){
        axis = ObjectAxisX;
    }else if(ctrl->GetId() == TRANSFORM_COMPONENT_POSITION_Y){
        axis = ObjectAxisY;
    }else if(ctrl->GetId() == TRANSFORM_COMPONENT_POSITION_Z){
        axis = ObjectAxisZ;
    }

    inspector->getMap()->getSelectionManager()->setSelectionPosition(ctrl->getIntValue(), axis);
    inspector->getMainFrame()->getCanvas()->renderFrame();
}

void ObjectTransformComponent::checkEnter(wxCommandEvent &event){
    pushInformation((NumberTextCtrl*)event.GetEventObject());
}
