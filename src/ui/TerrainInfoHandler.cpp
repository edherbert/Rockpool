#include "TerrainInfoHandler.h"

TerrainInfoHandler::TerrainInfoHandler(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    //wxPanel *mainPanel = new wxPanel(mainFrame);

    wxAuiPaneInfo info;
    //info.DestroyOnClose(false);
    info.Caption(wxT("Terrain Information"));
    info.Left();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("TerrainInformation"));
    auiManager->AddPane(this, info);

    noTerrainText = new wxStaticText(this, wxID_ANY, wxT("No valid terrain chunk provided."));
    //noTerrainText->Hide();
    wxBoxSizer *mainPanelVertical = new wxBoxSizer(wxVERTICAL);

    contentPanel = new wxPanel(this);
    wxBoxSizer *contentPanelVertical = new wxBoxSizer(wxVERTICAL);


    terrainPositionText = new wxStaticText(contentPanel, wxID_ANY, wxT("Terrain 0,0"));
    terrainPositionText->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer *terrainNameHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *terrainNameText = new wxStaticText(contentPanel, wxID_ANY, wxT("Terrain Name:"));
    terrainNameCtrl = new wxTextCtrl(contentPanel, wxID_ANY, wxEmptyString);
    terrainNameHorizontal->Add(terrainNameText, 0, wxRIGHT, 10);
    terrainNameHorizontal->Add(terrainNameCtrl, 1, wxEXPAND);



    wxStaticBoxSizer *terrainLayersStaticBox = new wxStaticBoxSizer(wxVERTICAL, contentPanel, wxT("Terrain Layers"));

    wxScrolledWindow *layerListPanel = new wxScrolledWindow(contentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    //layerListPanel->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_ALWAYS);

    wxBoxSizer *layerListSizer = new wxBoxSizer(wxVERTICAL);
    layerListPanel->SetSizer(layerListSizer);

    for(int i = 0; i < maxLayers; i++){
        TerrainInfoLayerBox *layer = new TerrainInfoLayerBox(layerListPanel, layerListSizer, this);
        layerBoxes.push_back(layer);
    }

    wxBoxSizer *terrainButtonsHorizontal = new wxBoxSizer(wxHORIZONTAL);
    newLayerButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_NEW_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    moveLayerUpButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_UP_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    moveLayerDownButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_DOWN_LAYER_BUTTON, wxBitmap(wxT("../media/img/icon.png")));
    deleteLayerButton = new wxBitmapButton(contentPanel, TERRAIN_INFO_DELETE_LAYER_BUTTON, wxBitmap(wxT("../media/img/rubbish.png")));

    refreshButton = new wxButton(contentPanel, TERRAIN_INFO_REFRESH, wxT("Refresh"));

    terrainButtonsHorizontal->Add(newLayerButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(moveLayerUpButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(moveLayerDownButton, 0, wxALL, 5);
    terrainButtonsHorizontal->Add(refreshButton, 0, wxALL, 5);
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
    SetSizer(mainPanelVertical);

    layerListPanel->SetScrollbars(5, 5, 1400, 2000);

    for(int i = 0; i < 3; i++){
        terrainInformation info;
        info.layerName = std::to_string(std::rand());
        info.layerNum = 1;

        layerInformation.push_back(info);
    }

    setTerrainInfoVisability(false);
    //Set the current terrain to nothing, so that nothing is shown in the dialog to start
    setCurrentTerrain(0);
    contentPanel->Hide();

    updateCheckButtons();
    updateLayerBoxes();

    Connect(TERRAIN_INFO_NEW_LAYER_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TerrainInfoHandler::newLayerButtonPressed));
    Connect(TERRAIN_INFO_DELETE_LAYER_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TerrainInfoHandler::deleteLayerButtonPressed));
    Connect(TERRAIN_INFO_REFRESH, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TerrainInfoHandler::refreshButtonPressed));
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

        layerbox->Layout();
    }

    if(layerInformation.size() >= maxLayers){
        newLayerButton->Disable();
    }else{
        newLayerButton->Enable();
    }

    for(int i = 0; i < layerInformation.size(); i++){
        layerBoxes[i]->setInfo(layerInformation[i].layerName);
    }

    auiManager->Update();
}

void TerrainInfoHandler::setCurrentTerrain(Ogre::Terrain *currentTerrain){
    //No point in doing all this if the terrain is the same
    if(this->currentTerrain == currentTerrain) return;

    this->currentTerrain = currentTerrain;
    if(!currentTerrain){
    //No terrain message
        noTerrainText->Show();
        contentPanel->Hide();
    }else{
    //Show terrain info
        noTerrainText->Hide();
        updateTerrainInformation();
        contentPanel->Show();
        Layout();
    }
}

void TerrainInfoHandler::updateTerrainInformation(){
    if(!currentTerrain) return;
    //terrainPositionText.SetLabel()
    //std::cout << currentTerrain->getTerrain

    //Get the name of the texture, depending on the layer number and the id of the texture in that list (both starting at 0)
    //std::cout << currentTerrain->getLayerTextureName(0, 0) << std::endl;

    //Get the size of each terrain texutre, depending on the index of the layer
    //std::cout << currentTerrain->getLayerWorldSize(0) << std::endl;

    //Get the number of layers in that terrain
    //std::cout << (int)currentTerrain->getLayerCount() << std::endl;

    int pointX = currentTerrain->getPosition().x / currentTerrain->getWorldSize();
    int pointZ = currentTerrain->getPosition().z / currentTerrain->getWorldSize();

    //Flip the z axis so that it's positive.
    terrainPositionText->SetLabel("Terrain " + std::to_string(pointX) + "," + std::to_string(-1 * pointZ));

    layerInformation.clear();

    for(int i = 0; i < (int)currentTerrain->getLayerCount(); i++){
        terrainInformation info;
        info.layerName = currentTerrain->getLayerTextureName(i, 0);
        info.layerNum = 0;

        layerInformation.push_back(info);
    }
    for(int i = 0; i < layerBoxes.size(); i++){
        layerBoxes[i]->setChecked(false);
    }

    updateLayerBoxes();
}

void TerrainInfoHandler::newLayerButtonPressed(wxCommandEvent &event){
    if(layerInformation.size() >= maxLayers)return;

    terrainInformation secondInfo;
    secondInfo.layerName = std::to_string(std::rand());
    secondInfo.layerNum = 1;

    layerInformation.push_back(secondInfo);

    updateLayerBoxes();
}

void TerrainInfoHandler::deleteLayerButtonPressed(wxCommandEvent &event){
    for(int i = 0; i < layerBoxes.size(); i++){
        if(layerBoxes[i]->isChecked()) layerInformation[i].shouldRemove = true;
        layerBoxes[i]->setChecked(false);
    }
    for(int i = layerInformation.size() - 1; i >= 0; i--){
        if(layerInformation[i].shouldRemove)layerInformation.erase(layerInformation.begin() + i);
    }

    updateLayerBoxes();
    updateCheckButtons();
}

void TerrainInfoHandler::refreshButtonPressed(wxCommandEvent &event){
    if(!currentTerrain)return;

    std::cout << (int)currentTerrain->getLayerCount() << std::endl;

    for(int i = 0; i < layerInformation.size(); i++){
        Ogre::StringVector paths;
        paths.push_back(layerBoxes[i]->getInfo());
        paths.push_back("dirt_grayrocky_normalheight.dds");

        if(i >= (int)currentTerrain->getLayerCount()){
            currentTerrain->addLayer((Ogre::Real)100, &paths);
        }else{
            currentTerrain->replaceLayer((Ogre::uint8)i, true, (Ogre::Real)100, &paths);
        }
    }
    for(int i = 0; i < (int)currentTerrain->getLayerCount(); i++){
        if(i >= layerInformation.size()){
            currentTerrain->removeLayer(i);
        }
    }
}
