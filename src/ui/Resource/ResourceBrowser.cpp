#include "ResourceBrowser.h"

ResourceBrowser::ResourceBrowser(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxAuiPaneInfo info;
    info.Caption(wxT("Resource Browser"));
    info.Left();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("ResourceBrowser"));
    auiManager->AddPane(this, info);

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxSearchCtrl *searchBar = new wxSearchCtrl(this, wxID_ANY);
    searchBar->ShowCancelButton(true);

    vertical->Add(searchBar, 0, wxEXPAND | wxALL, 10);

    resPanel = new ResourcePanel(this, mainFrame->getResourceManager());
    vertical->Add(resPanel, 1, wxEXPAND);

    setResourceBrowserVisability(false);

    SetSizer(vertical);
}

ResourceBrowser::~ResourceBrowser(){

}

void ResourceBrowser::setResourceBrowserVisability(bool visible){
    if(visible){
        auiManager->GetPane(wxT("ResourceBrowser")).Show();
        mainFrame->showResourceBrowser->Check(true);
    }else{
        auiManager->GetPane(wxT("ResourceBrowser")).Hide();
        mainFrame->showResourceBrowser->Check(false);
    }
    auiManager->Update();
    browserVisible = visible;
}

void ResourceBrowser::updateTiles(){
    resPanel->updateTiles();
}

void ResourceBrowser::layoutTiles(){
    resPanel->layoutTiles();
}
