#include "ResourceBrowser.h"

ResourceBrowser::ResourceBrowser(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxAuiPaneInfo info;
    info.Caption(wxT("Resource Browser"));
    info.Right();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("ResourceBrowser"));
    auiManager->AddPane(this, info);

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxSearchCtrl *searchBar = new wxSearchCtrl(this, wxID_ANY);
    searchBar->ShowCancelButton(true);

    vertical->Add(searchBar, 0, wxEXPAND | wxALL, 10);


    scrollWindow = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer *scrollWindowSizer = new wxBoxSizer(wxVERTICAL);
    scrollWindow->SetSizer(scrollWindowSizer);

    resPanel = new ResourcePanel(scrollWindow, mainFrame->getResourceManager());

    scrollWindowSizer->Add(resPanel, 1, wxEXPAND);

    vertical->Add(scrollWindow, 1, wxEXPAND);

    setResourceBrowserVisability(false);

    SetSizer(vertical);

    scrollWindow->SetScrollbars(5, 5, 0, 0);

    Connect(wxEVT_SIZE, wxSizeEventHandler(ResourceBrowser::resourceBrowserResize));
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

void ResourceBrowser::resourceBrowserResize(wxSizeEvent &event){
    int width, height;
    resPanel->GetSize(&width, &height);

    Layout();
}
