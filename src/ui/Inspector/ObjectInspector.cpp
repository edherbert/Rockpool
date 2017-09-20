#include "ObjectInspector.h"

#include <wx/aui/aui.h>
#include <wx/menuitem.h>

#include "../MainFrame.h"
#include "ObjectNameComponent.h"

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

    nameComponent = new ObjectNameComponent(this);

    addObjectComponent(nameComponent);

    //Create the items manually, cos there isn't going to be that many.
    //When an object is selected, calls to each individual component can be made.
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
