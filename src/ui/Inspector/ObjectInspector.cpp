#include "ObjectInspector.h"

#include <wx/aui/aui.h>
#include <wx/menuitem.h>

#include "../MainFrame.h"
#include "ObjectNameComponent.h"
#include "ObjectTransformComponent.h"
#include "NoSelectionComponent.h"

ObjectInspector::ObjectInspector(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxAuiPaneInfo info;
    info.Caption(wxT("Object Inspector"));
    info.Right();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("ObjectInspector"));
    auiManager->AddPane(this, info);

    setObjectInspectorVisability(false);


    mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    noSelectionComponent = new NoSelectionComponent(this);
    nameComponent = new ObjectNameComponent(this);
    transformComponent = new ObjectTransformComponent(this);

    addObjectComponent(noSelectionComponent);
    addObjectComponent(nameComponent);
    addObjectComponent(transformComponent);
}

ObjectInspector::~ObjectInspector(){

}

void ObjectInspector::setObjectInspectorVisability(bool visible){
    if(visible){
        auiManager->GetPane(wxT("ObjectInspector")).Show();
        mainFrame->showObjectInspector->Check(true);
    }else{
        auiManager->GetPane(wxT("ObjectInspector")).Hide();
        mainFrame->showObjectInspector->Check(false);
    }
    auiManager->Update();
    inspectorVisible = visible;
}

void ObjectInspector::addObjectComponent(InspectorComponent *component){
    mainSizer->Add(component, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
}

void ObjectInspector::updateSelection(){

}
