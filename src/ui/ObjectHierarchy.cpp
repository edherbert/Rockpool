#include "ObjectHierarchy.h"

ObjectHierarchy::ObjectHierarchy(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxAuiPaneInfo info;
    info.Caption(wxT("Object Hierarchy"));
    info.Left();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("ObjectHierarchy"));
    auiManager->AddPane(this, info);
}

ObjectHierarchy::~ObjectHierarchy(){

}

void ObjectHierarchy::setObjectHierarchyVisible(bool visible){
    if(visible){
        auiManager->GetPane(wxT("ObjectHierarchy")).Show();
        mainFrame->showObjectHierarchy->Check(true);
    }else{
        auiManager->GetPane(wxT("ObjectHierarchy")).Hide();
        mainFrame->showObjectHierarchy->Check(false);
    }
    auiManager->Update();
    hierarchyVisible = visible;
}
