#include "ToolsPanelHandler.h"

ToolsPanelHandler::ToolsPanelHandler(MainFrame *mainFrame, wxAuiManager *auiManager) : wxApp(){
    this->auiManager = auiManager;
    this->mainFrame = mainFrame;

    wxBitmap bitmap(wxT("../media/img/icon.png"));
    toolbar = new wxAuiToolBar(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    toolbar->SetToolBitmapSize(wxSize(20, 23));

    toolbar->AddTool(TOOL_PANEL_TERRAIN_EDIT, bitmap, bitmap, true);
    toolbar->AddTool(TOOL_PANEL_TERRAIN_TEXTURE, bitmap, bitmap, true);
    toolbar->AddTool(TOOL_PANEL_TERRAIN_HEIGHT, bitmap, bitmap, true);
    toolbar->AddTool(TOOL_PANEL_TERRAIN_SMOOTH, bitmap, bitmap, true);

    tools[0] = TOOL_PANEL_TERRAIN_EDIT;
    tools[1] = TOOL_PANEL_TERRAIN_TEXTURE;
    tools[2] = TOOL_PANEL_TERRAIN_HEIGHT;
    tools[3] = TOOL_PANEL_TERRAIN_SMOOTH;

    auiManager->AddPane(toolbar, wxAuiPaneInfo().Name(wxT("Terrains Toolbar")).Caption(wxT("Terrains Toolbar")).ToolbarPane().Top());
    toolbar->Realize();

    Connect(TOOL_PANEL_TERRAIN_EDIT, wxEVT_TOOL, wxCommandEventHandler(ToolsPanelHandler::terrainEditToolCallback));
    Connect(TOOL_PANEL_TERRAIN_TEXTURE, wxEVT_TOOL, wxCommandEventHandler(ToolsPanelHandler::terrainTextureToolCallback));
    Connect(TOOL_PANEL_TERRAIN_HEIGHT, wxEVT_TOOL, wxCommandEventHandler(ToolsPanelHandler::terrainHeightToolCallback));
    Connect(TOOL_PANEL_TERRAIN_SMOOTH, wxEVT_TOOL, wxCommandEventHandler(ToolsPanelHandler::terrainSmoothToolCallback));

    //setTool(TOOL_PANEL_TERRAIN_EDIT);
    setTool(TOOL_PANEL_TERRAIN_TEXTURE);

    setToolPanelVisibility(false);
}

ToolsPanelHandler::~ToolsPanelHandler(){

}

void ToolsPanelHandler::setTool(int toolId){
    for(int i = 0; i < sizeof(tools) / sizeof(int); i++){
        toolbar->ToggleTool(tools[i], false);
    }
    currentTool = toolId;
    toolbar->ToggleTool(toolId, true);
    mainFrame->getToolPreferencesHandler()->setToolPreference(toolId);
}

void ToolsPanelHandler::terrainEditToolCallback(wxCommandEvent &event){
    setTool(TOOL_PANEL_TERRAIN_EDIT);
}

void ToolsPanelHandler::terrainTextureToolCallback(wxCommandEvent &event){
    setTool(TOOL_PANEL_TERRAIN_TEXTURE);
}

void ToolsPanelHandler::terrainHeightToolCallback(wxCommandEvent &event){
    setTool(TOOL_PANEL_TERRAIN_HEIGHT);
}

void ToolsPanelHandler::terrainSmoothToolCallback(wxCommandEvent &event){
    setTool(TOOL_PANEL_TERRAIN_SMOOTH);
}

int ToolsPanelHandler::getCurrentTool(){
    return currentTool;
}

void ToolsPanelHandler::setToolPanelVisibility(bool val){
    if(val) toolbar->Show();
    else toolbar->Hide();
    mainFrame->showTerrainToolbar->Check(val);

    auiManager->Update();
}
