#include "ObjectInspector.h"

#include <wx/aui/aui.h>
#include <wx/menuitem.h>

#include "../MainFrame.h"

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
