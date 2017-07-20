#include "ToolPreferencesHandler.h"

ToolPreferencesHandler::ToolPreferencesHandler(MainFrame *mainFrame, wxAuiManager *auiManager){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;
    //this->parentPanel = parentPanel;

    parentPanel = new wxPanel(mainFrame);

    editPreferences = new TerrainEditToolPreferences(parentPanel);
    texturePreferences = new TerrainTextureToolPreferences(parentPanel);
    terrainHeightPreferences = new TerrainHeightToolPreferences(parentPanel);


    preferences.push_back(editPreferences);
    preferences.push_back(texturePreferences);
    preferences.push_back(terrainHeightPreferences);


    wxAuiPaneInfo info;
    //info.DestroyOnClose(false);
    info.Caption(wxT("Tool Preferences"));
    info.Right();
    info.BestSize(wxSize(400, 400));
    info.Show(false);
    info.Name(wxT("ToolPreferences"));
    auiManager->AddPane(parentPanel, info);

    setToolPreference(TOOL_PANEL_TERRAIN_EDIT);
}

ToolPreferencesHandler::~ToolPreferencesHandler(){

}

void ToolPreferencesHandler::setToolPreference(int toolID){
    for(int i = 0; i < preferences.size(); i++){
        if(preferences.at(i)->getId() == toolID) preferences.at(i)->show(true);
        else preferences.at(i)->show(false);
    }
}

ToolPreferences* ToolPreferencesHandler::getToolById(int id){
    ToolPreferences *preference;
    for(int i = 0; i < preferences.size(); i++){
        if(preferences.at(i)->getId() == id) preference = preferences.at(i);
    }
    if(!preference){
        std::cout << "Could not find a tool with that id!" << std::endl;
    }
    return preference;
}

TerrainEditToolPreferences* ToolPreferencesHandler::getTerrainEditTool(){
    return editPreferences;
}

TerrainTextureToolPreferences* ToolPreferencesHandler::getTerrainTextureTool(){
    return texturePreferences;
}

TerrainHeightToolPreferences* ToolPreferencesHandler::getTerrainHeightTool(){
    return terrainHeightPreferences;
}

void ToolPreferencesHandler::setToolPreferencesVisability(bool visible){
    if(visible){
        auiManager->GetPane(wxT("ToolPreferences")).Show();
        mainFrame->showToolPreferences->Check(true);
    }
    else {
        auiManager->GetPane(wxT("ToolPreferences")).Hide();
        mainFrame->showToolPreferences->Check(false);
    }

    auiManager->Update();
    toolPreferencesVisible = visible;
}
