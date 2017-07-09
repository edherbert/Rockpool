#include "TerrainInfoHandler.h"

TerrainInfoHandler::TerrainInfoHandler(MainFrame *mainFrame, wxAuiManager *auiManager){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxPanel *mainPanel = new wxPanel(mainFrame);

    wxAuiPaneInfo info;
    //info.DestroyOnClose(false);
    info.Caption(wxT("Terrain Information"));
    info.Left();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("TerrainInformation"));
    auiManager->AddPane(mainPanel, info);

    wxStaticText *noTerrainText = new wxStaticText(mainPanel, wxID_ANY, wxT("No valid terrain chunk provided."));
    noTerrainText->Hide();
    wxBoxSizer *mainPanelVertical = new wxBoxSizer(wxVERTICAL);

    wxPanel *contentPanel = new wxPanel(mainPanel);
    wxBoxSizer *contentPanelVertical = new wxBoxSizer(wxVERTICAL);


    wxStaticText *terrainPositionText = new wxStaticText(contentPanel, wxID_ANY, wxT("Terrain 0,0"));
    terrainPositionText->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *terrainNameHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *terrainNameText = new wxStaticText(contentPanel, wxID_ANY, wxT("Terrain Name:"));
    wxTextCtrl *terrainNameCtrl = new wxTextCtrl(contentPanel, wxID_ANY, wxEmptyString);
    terrainNameHorizontal->Add(terrainNameText, 0, wxRIGHT, 10);
    terrainNameHorizontal->Add(terrainNameCtrl, 1, wxEXPAND);



    wxStaticBoxSizer *terrainLayersStaticBox = new wxStaticBoxSizer(wxVERTICAL, contentPanel, wxT("Terrain Layers"));

    wxScrolledWindow *layerListPanel = new wxScrolledWindow(contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    //layerListPanel->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_ALWAYS);

    wxBoxSizer *layerListSizer = new wxBoxSizer(wxVERTICAL);
    layerListPanel->SetSizer(layerListSizer);

    /*TerrainInfoLayerBox *first = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);
    TerrainInfoLayerBox *second = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);
    TerrainInfoLayerBox *third = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);
    TerrainInfoLayerBox *fourth = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);

    layerBoxes.push_back(first);
    layerBoxes.push_back(second);
    layerBoxes.push_back(third);
    layerBoxes.push_back(fourth);*/

    for(int i = 0; i < maxLayers; i++){
        TerrainInfoLayerBox *layer = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);
        layerBoxes.push_back(layer);
    }

    wxBoxSizer *terrainButtonsHorizontal = new wxBoxSizer(wxHORIZONTAL);
    newLayerButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_NEW_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    moveLayerUpButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_UP_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    moveLayerDownButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_DOWN_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    deleteLayerButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_DELETE_LAYER_BUTTON, wxBitmap(wxT("../media/img/rubbish.png")));

    terrainButtonsHorizontal->Add(newLayerButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(moveLayerUpButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(moveLayerDownButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(new wxPanel(contentPanel), 1, wxEXPAND);
    terrainButtonsHorizontal->Add(deleteLayerButton, 0, wxALL, 5);

    terrainLayersStaticBox->Add(layerListPanel, 1, wxEXPAND);
    terrainLayersStaticBox->Add(new wxStaticLine(contentPanel), 0, wxEXPAND);
    terrainLayersStaticBox->Add(terrainButtonsHorizontal, 0, wxEXPAND);


    wxCheckBox *terrainUseNormalMap = new wxCheckBox(contentPanel, wxID_ANY, wxT("Use Normal Map"));

    contentPanelVertical->Add(terrainPositionText, 0, wxALL, 10);
    contentPanelVertical->Add(terrainNameHorizontal, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    contentPanelVertical->Add(terrainLayersStaticBox, 1, wxEXPAND | wxALL, 10);
    contentPanelVertical->Add(terrainUseNormalMap, 0, wxLEFT, 10);

    contentPanel->SetSizer(contentPanelVertical);

    mainPanelVertical->Add(contentPanel, 1, wxEXPAND);
    mainPanel->SetSizer(mainPanelVertical);

    layerListPanel->SetScrollbars(5, 5, 1400, 2000);

    terrainInformation firstInfo;
    firstInfo.layerName = "First";
    firstInfo.layerNum = 1;

    terrainInformation secondInfo;
    secondInfo.layerName = "Second";
    secondInfo.layerNum = 2;

    layerInformation.push_back(firstInfo);
    layerInformation.push_back(secondInfo);

    setTerrainInfoVisability(false);
    updateCheckButtons();
    updateLayerBoxes();

    contentPanel->Connect(TERRAIN_INFO_NEW_LAYER_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TerrainInfoHandler::newLayerButtonPressed));
    contentPanel->Connect(TERRAIN_INFO_DELETE_LAYER_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TerrainInfoHandler::deleteLayerButtonPressed));
}

TerrainInfoHandler::~TerrainInfoHandler(){

}

void TerrainInfoHandler::setTerrainInfoVisability(bool visible){
    if(visible){
        auiManager->GetPane(wxT("TerrainInformation")).Show();
        mainFrame->showTerrainInfo->Check(true);
    }
    else {
        auiManager->GetPane(wxT("TerrainInformation")).Hide();
        mainFrame->showTerrainInfo->Check(false);
    }

    auiManager->Update();
    terrainInfoVisible = visible;
}

void TerrainInfoHandler::updateCheckButtons(){
    bool anyChecked = false;
    for(TerrainInfoLayerBox *layerBox : layerBoxes){
        if(layerBox->isChecked()) anyChecked = true;
    }

    if(!anyChecked){
        moveLayerUpButton->Disable();
        moveLayerDownButton->Disable();
        deleteLayerButton->Disable();
    }else{
        moveLayerUpButton->Enable();
        moveLayerDownButton->Enable();
        deleteLayerButton->Enable();
    }
}

void TerrainInfoHandler::updateLayerBoxes(){
    for(int i = 0; i < layerBoxes.size(); i++){
        TerrainInfoLayerBox *layerbox = layerBoxes.at(i);

        if(i >= layerInformation.size()) layerbox->Hide();
        else layerbox->Show();

    }

    if(layerInformation.size() >= maxLayers){
        newLayerButton->Disable();
    }else{
        newLayerButton->Enable();
    }
}

void TerrainInfoHandler::updateInformation(){

}

void TerrainInfoHandler::newLayerButtonPressed(wxCommandEvent &event){
    std::cout << "pressed" << std::endl;
}

void TerrainInfoHandler::deleteLayerButtonPressed(wxCommandEvent &event){
    std::cout << "delete" << std::endl;
    std::cout << layerInformation.size() << std::endl;
}
