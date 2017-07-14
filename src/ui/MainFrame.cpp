#include <iostream>
#include <wx/wx.h>

#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MAXIMIZE(MainFrame::onMaximize)
END_EVENT_TABLE()

MainFrame::MainFrame(Main *main, const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 1000)){
    this->main = main;
    setupMenuBar();

    SetMinSize(wxSize(500, 500));

    auiManager = new wxAuiManager(this, wxAUI_MGR_LIVE_RESIZE | wxAUI_MGR_DEFAULT);

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    canvas = new GLCanvas(this, args, 0);
    main->setCanvas(canvas);

    //Setup the preferences for the tool
    toolPreferencesHandler = new ToolPreferencesHandler(this, auiManager);
    toolPreferencesHandler->setToolPreferencesVisability(true);

    terrainInfoHandler = new TerrainInfoHandler(this, auiManager);
    terrainInfoHandler->setTerrainInfoVisability(true);

    //The tools panel that appears at the top of the window.
    toolPanelHandler = new ToolsPanelHandler(this, auiManager);
    toolPanelHandler->setToolPanelVisibility(true);

    handlerData.toolPreferencesHandler = toolPreferencesHandler;
    handlerData.terrainInfoHandler = terrainInfoHandler;
    handlerData.toolPanelHandler = toolPanelHandler;

    auiManager->AddPane(canvas, wxCENTRE);
    auiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 5);

    timer = new RenderTimer(canvas);
    timer->start();

    Connect(wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler(MainFrame::closeToolPreferences));

    auiManager->Update();

    Maximize();

    MapPropertiesDialog dialog(this);
}

MainFrame::~MainFrame(){
    auiManager->UnInit();
}

void MainFrame::onMaximize(wxMaximizeEvent &evt){
    //splitWindow->SetSashPosition(1300, true);
}

void MainFrame::setupMenuBar(){
    SetIcon(wxIcon(wxT("../media/img/icon.png")));

    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *file = new wxMenu;
    wxMenu *edit = new wxMenu;
    wxMenu *view = new wxMenu;
    wxMenu *map = new wxMenu;
    wxMenu *window = new wxMenu;

    file->Append(MENU_FILE_NEW_MAP, wxT("New Map\tctrl+N"));
    file->Append(MENU_FILE_OPEN_MAP, wxT("Open Map\tctrl+O"));
    file->AppendSeparator();
    file->Append(wxID_ANY, wxT("Recent"));

    edit->Append(wxID_ANY, wxT("Undo"));
    edit->Append(wxID_ANY, wxT("Redo"));
    edit->AppendSeparator();
    edit->Append(wxID_ANY, wxT("Cut"));
    edit->Append(wxID_ANY, wxT("Copy"));
    edit->Append(wxID_ANY, wxT("Paste"));
    edit->Append(wxID_ANY, wxT("Delete"));

    view->Append(wxID_ANY, wxT("Zoom"));
    view->Append(wxID_ANY, wxT("Show Grid"));

    map->Append(MENU_MAP_MAP_PROPERTIES, wxT("Map Properties"));

    wxMenu *dockableWindows = new wxMenu;
    wxMenu *toolbars = new wxMenu;

    //All of these should be checked to false to begin with
    //They will be activated by functions later
    showToolPreferences = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_TOOL_PREFERENCES, wxT("Show Tool Preferences"), wxEmptyString, wxITEM_CHECK);
    showTerrainInfo = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_TERRAIN_INFO, wxT("Show Terrain Info"), wxEmptyString, wxITEM_CHECK);
    dockableWindows->Append(showToolPreferences);
    dockableWindows->Append(showTerrainInfo);
    showToolPreferences->Check(false);

    showTerrainToolbar = new wxMenuItem(toolbars, MENU_WINDOW_SHOW_TERRAIN_TOOLBAR, wxT("Show Terrain Toolbar"), wxEmptyString, wxITEM_CHECK);
    toolbars->Append(showTerrainToolbar);
    showTerrainToolbar->Check(false);

//    window->Append(dockableWindows, wxT("Dockable Windows"));
    window->Append(wxID_ANY, wxT("Dockable Windows"), dockableWindows);
    window->Append(wxID_ANY, wxT("Toolbars"), toolbars);

    menuBar->Append(file, wxT("&File"));
    menuBar->Append(edit, wxT("&Edit"));
    menuBar->Append(view, wxT("&View"));
    menuBar->Append(map, wxT("&Map"));
    menuBar->Append(window, wxT("&Window"));

    Connect(MENU_FILE_NEW_MAP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::newMap));
    Connect(MENU_FILE_OPEN_MAP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::openMap));

    Connect(MENU_MAP_MAP_PROPERTIES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::openMapProperties));

    Connect(MENU_WINDOW_SHOW_TOOL_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowToolPreferences));
    Connect(MENU_WINDOW_SHOW_TERRAIN_INFO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowTerrainInfo));

    Connect(MENU_WINDOW_SHOW_TERRAIN_TOOLBAR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowTerrainToolbar));

    SetMenuBar(menuBar);
}

void MainFrame::newMap(wxCommandEvent& WXUNUSED(event)){
    NewMapDialog dialog(this, main);
}

void MainFrame::openMap(wxCommandEvent& WXUNUSED(event)){
    wxFileDialog *dialog = new wxFileDialog(this, "Select a Rockpool file.", "", "", "Rockpool files (*.rockpool)|*.rockpool");
    if(dialog->ShowModal() != wxID_CANCEL){
        main->loadMap(this, dialog->GetPath(), dialog->GetDirectory());
    }
}

void MainFrame::openMapProperties(wxCommandEvent& WXUNUSED(event)){
    MapPropertiesDialog dialog(this);
}

void MainFrame::ShowToolPreferences(wxCommandEvent &event){
    toolPreferencesHandler->setToolPreferencesVisability(event.IsChecked());
}

void MainFrame::ShowTerrainInfo(wxCommandEvent &event){
    terrainInfoHandler->setTerrainInfoVisability(event.IsChecked());
}

void MainFrame::ShowTerrainToolbar(wxCommandEvent &event){
    toolPanelHandler->setToolPanelVisibility(event.IsChecked());
}

ToolPreferencesHandler* MainFrame::getToolPreferencesHandler(){
    return toolPreferencesHandler;
}

TerrainInfoHandler* MainFrame::getTerrainInfoHandler(){
    return terrainInfoHandler;
}

HandlerData* MainFrame::getHandlerData(){
    return &handlerData;
}

void MainFrame::closeToolPreferences(wxAuiManagerEvent &event){
//Change the name of this function at some point
    if(event.GetPane()->name == "ToolPreferences"){
        toolPreferencesHandler->setToolPreferencesVisability(false);
    }
    if(event.GetPane()->name == "TerrainInformation"){
        terrainInfoHandler->setTerrainInfoVisability(false);
    }
}
