#include "ObjectInspector.h"

#include <wx/aui/aui.h>
#include <wx/menuitem.h>

#include "../MainFrame.h"
#include "../../map/Main.h"
#include "ObjectNameComponent.h"
#include "ObjectTransformComponent.h"
#include "NoSelectionComponent.h"
#include "../Hierarchy/ObjectHierarchy.h"
#include "../Hierarchy/HierarchyTree.h"

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

    updateComponents();
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

void ObjectInspector::updateComponents(){
    int selectionCount = mainFrame->getObjectHierarchy()->getTree()->getSelectionCount();

    if(selectionCount <= 0){
        noSelection();
    }else if(selectionCount == 1){
        singleSelection();

        Object *object = mainFrame->getObjectHierarchy()->getTree()->getFirstSelectionObject();
        nameComponent->updateInformation(object);
        transformComponent->updateInformation(mainFrame->getMain()->getCurrentMap()->getSelectionManager());
    }else{
        noSelectionComponent->Show();
        nameComponent->Hide();
        transformComponent->Hide();
    }
    Layout();
}

void ObjectInspector::noSelection(){
    noSelectionComponent->Show();
    nameComponent->Hide();
    transformComponent->Hide();
}

void ObjectInspector::singleSelection(){
    noSelectionComponent->Hide();
    nameComponent->Show();
    transformComponent->Show();
}

MainFrame* ObjectInspector::getMainFrame(){
    return mainFrame;
}

void ObjectInspector::setMap(Map *map){
    this->map = map;
}

Map* ObjectInspector::getMap(){
    return map;
}
