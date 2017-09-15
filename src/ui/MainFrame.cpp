#include "MainFrame.h"
#include <iostream>

#include "wxIDs.h"
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/splitter.h>

#include "GLCanvas.h"
#include "../map/Main.h"
#include "Dialogs/NewMapDialog.h"
#include "RenderTimer.h"
#include "Dialogs/MapPropertiesDialog.h"
#include "Tools/ToolPreferencesHandler.h"
#include "Tools/ToolsPanelHandler.h"
#include "TerrainInfoHandler.h"
#include "Resource/ResourceBrowser.h"
#include "../system/ResourceManager.h"
#include "Hierarchy/ObjectHierarchy.h"

#include "Dialogs/MapPropertiesSkyBoxDialog.h"

MainFrame::MainFrame(Main *main, const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 1000)){
    this->main = main;
    setupMenuBar();

    SetMinSize(wxSize(500, 500));

    auiManager = new wxAuiManager(this, wxAUI_MGR_LIVE_RESIZE | wxAUI_MGR_DEFAULT);

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    canvas = new GLCanvas(this, args, 0);
    main->setCanvas(canvas);

    //Setup the panels
    toolPreferencesHandler = new ToolPreferencesHandler(this, auiManager);
    //toolPreferencesHandler->setToolPreferencesVisability(true);

    terrainInfoHandler = new TerrainInfoHandler(this, auiManager);
    //terrainInfoHandler->setTerrainInfoVisability(true);

    resourceBrowser = new ResourceBrowser(this, auiManager);
    resourceBrowser->setResourceBrowserVisability(true);

    objectHierarchy = new ObjectHierarchy(this, auiManager);
    objectHierarchy->setObjectHierarchyVisible(true);

    toolPanelHandler = new ToolsPanelHandler(this, auiManager);
    toolPanelHandler->setToolPanelVisibility(true);

    handlerData.toolPreferencesHandler = toolPreferencesHandler;
    handlerData.terrainInfoHandler = terrainInfoHandler;
    handlerData.toolPanelHandler = toolPanelHandler;

    auiManager->AddPane(canvas, wxCENTRE);
    auiManager->GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 5);

    timer = new RenderTimer(canvas);
    timer->start();

    Connect(wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler(MainFrame::AUIPanelClosed));

    auiManager->Update();

    //MapPropertiesSkyBoxDialog dialog(this);

    Maximize();
}

MainFrame::~MainFrame(){
    auiManager->UnInit();
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
    file->Append(wxID_ANY, wxT("Recent"));
    file->AppendSeparator();
    file->Append(MENU_FILE_SAVE_MAP, wxT("Save\tctrl+S"));
    file->Append(wxID_ANY, wxT("Export\tctrl+shift+E"));
    file->Append(wxID_ANY, wxT("Export As Previous\tctrl+E"));

    edit->Append(MENU_EDIT_UNDO, wxT("Undo\tctrl+Z"));
    edit->Append(MENU_EDIT_REDO, wxT("Redo\tctrl+shift+Z"));
    edit->AppendSeparator();
    edit->Append(MENU_EDIT_CUT, wxT("Cut\tctrl+X"));
    edit->Append(MENU_EDIT_COPY, wxT("Copy\tctrl+C"));
    edit->Append(MENU_EDIT_PASTE, wxT("Paste\tctrl+V"));
    edit->Append(MENU_EDIT_DELETE, wxT("Delete"));
    edit->AppendSeparator();
    edit->Append(wxID_ANY, wxT("Rockpool Preferences"));

    view->Append(wxID_ANY, wxT("Zoom"));
    view->Append(wxID_ANY, wxT("Show Grid"));

    map->Append(MENU_MAP_MAP_PROPERTIES, wxT("Map Properties"));

    wxMenu *dockableWindows = new wxMenu;
    wxMenu *toolbars = new wxMenu;

    //All of these should be checked to false to begin with
    //They will be activated by functions later
    showToolPreferences = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_TOOL_PREFERENCES, wxT("Show Tool Preferences"), wxEmptyString, wxITEM_CHECK);
    showTerrainInfo = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_TERRAIN_INFO, wxT("Show Terrain Info"), wxEmptyString, wxITEM_CHECK);
    showResourceBrowser = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_RESOURCE_BROWSER, wxT("Show Resource Browser"), wxEmptyString, wxITEM_CHECK);
    showObjectHierarchy = new wxMenuItem(dockableWindows, MENU_WINDOW_SHOW_OBJECT_HIERARCHY, wxT("Show Object Hierarchy"), wxEmptyString, wxITEM_CHECK);
    dockableWindows->Append(showToolPreferences);
    dockableWindows->Append(showTerrainInfo);
    dockableWindows->Append(showResourceBrowser);
    dockableWindows->Append(showObjectHierarchy);

    showTerrainToolbar = new wxMenuItem(toolbars, MENU_WINDOW_SHOW_TERRAIN_TOOLBAR, wxT("Show Terrain Toolbar"), wxEmptyString, wxITEM_CHECK);
    toolbars->Append(showTerrainToolbar);

    window->Append(wxID_ANY, wxT("Dockable Windows"), dockableWindows);
    window->Append(wxID_ANY, wxT("Toolbars"), toolbars);

    menuBar->Append(file, wxT("&File"));
    menuBar->Append(edit, wxT("&Edit"));
    menuBar->Append(view, wxT("&View"));
    menuBar->Append(map, wxT("&Map"));
    menuBar->Append(window, wxT("&Window"));

    Connect(MENU_FILE_NEW_MAP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::newMap));
    Connect(MENU_FILE_OPEN_MAP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::openMap));
    Connect(MENU_FILE_SAVE_MAP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::saveMap));

    Connect(MENU_MAP_MAP_PROPERTIES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::openMapProperties));

    Connect(MENU_WINDOW_SHOW_TOOL_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowToolPreferences));
    Connect(MENU_WINDOW_SHOW_TERRAIN_INFO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowTerrainInfo));
    Connect(MENU_WINDOW_SHOW_RESOURCE_BROWSER, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowResourceBrowser));
    Connect(MENU_WINDOW_SHOW_OBJECT_HIERARCHY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowObjectHierarchy));

    Connect(MENU_WINDOW_SHOW_TERRAIN_TOOLBAR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::ShowTerrainToolbar));

    Connect(MENU_EDIT_UNDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::undoAction));
    Connect(MENU_EDIT_REDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::redoAction));
    Connect(MENU_EDIT_CUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::clipboardAction));
    Connect(MENU_EDIT_COPY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::clipboardAction));
    Connect(MENU_EDIT_PASTE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::clipboardAction));
    Connect(MENU_EDIT_DELETE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::clipboardAction));

    wxAcceleratorEntry entries[8];
    entries[0].Set(wxACCEL_CTRL, (int) 'N', MENU_FILE_NEW_MAP);
    entries[1].Set(wxACCEL_CTRL, (int) 'O', MENU_FILE_OPEN_MAP);
    entries[2].Set(wxACCEL_CTRL, (int) 'S', MENU_FILE_SAVE_MAP);

    entries[3].Set(wxACCEL_CTRL, (int) 'Z', MENU_EDIT_UNDO);
    entries[4].Set(wxACCEL_CTRL | wxACCEL_SHIFT, (int) 'Z', MENU_EDIT_REDO);

    entries[5].Set(wxACCEL_CTRL, (int) 'C', MENU_EDIT_COPY);
    entries[6].Set(wxACCEL_CTRL, (int) 'X', MENU_EDIT_CUT);
    entries[7].Set(wxACCEL_CTRL, (int) 'V', MENU_EDIT_PASTE);

    wxAcceleratorTable accel(8, entries);
    SetAcceleratorTable(accel);

    SetMenuBar(menuBar);
}

Main* MainFrame::getMain(){
    return main;
}

void MainFrame::newMap(wxCommandEvent &event){
    NewMapDialog dialog(this, main);
}

void MainFrame::openMap(wxCommandEvent &event){
    wxFileDialog *dialog = new wxFileDialog(this, "Select a Rockpool file.", "", "", "Rockpool files (*.rockpool)|*.rockpool");
    if(dialog->ShowModal() != wxID_CANCEL){
        main->loadMap(this, dialog->GetPath(), dialog->GetDirectory());
    }
}

void MainFrame::openMapProperties(wxCommandEvent& WXUNUSED(event)){
    MapPropertiesDialog dialog(this, this);
}

void MainFrame::ShowToolPreferences(wxCommandEvent &event){
    toolPreferencesHandler->setToolPreferencesVisability(event.IsChecked());
}

void MainFrame::undoAction(wxCommandEvent &event){
    main->undoAction();
}

void MainFrame::redoAction(wxCommandEvent &event){
    main->redoAction();
}

void MainFrame::ShowTerrainInfo(wxCommandEvent &event){
    terrainInfoHandler->setTerrainInfoVisability(event.IsChecked());
}

void MainFrame::ShowResourceBrowser(wxCommandEvent &event){
    resourceBrowser->setResourceBrowserVisability(event.IsChecked());
}

void MainFrame::ShowObjectHierarchy(wxCommandEvent &event){
    objectHierarchy->setObjectHierarchyVisible(event.IsChecked());
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

ResourceManager* MainFrame::getResourceManager(){
    return main->getResourceManager();
}

ResourceBrowser* MainFrame::getResourceBrowser(){
    return resourceBrowser;
}

HandlerData* MainFrame::getHandlerData(){
    return &handlerData;
}

void MainFrame::AUIPanelClosed(wxAuiManagerEvent &event){
//Change the name of this function at some point
    if(event.GetPane()->name == "ToolPreferences"){
        toolPreferencesHandler->setToolPreferencesVisability(false);
    }
    if(event.GetPane()->name == "TerrainInformation"){
        terrainInfoHandler->setTerrainInfoVisability(false);
    }
    if(event.GetPane()->name == "ResourceBrowser"){
        resourceBrowser->setResourceBrowserVisability(false);
    }
    if(event.GetPane()->name == "ObjectHierarchy"){
        objectHierarchy->setObjectHierarchyVisible(false);
    }
}

void MainFrame::saveMap(wxCommandEvent &event){
    main->saveProject();
}

GLCanvas* MainFrame::getCanvas(){
    return canvas;
}

ObjectHierarchy* MainFrame::getObjectHierarchy(){
    return objectHierarchy;
}

void MainFrame::clipboardAction(wxCommandEvent &event){
    if(event.GetId() == MENU_EDIT_COPY){
        objectHierarchy->copyItems();
    }else if(event.GetId() == MENU_EDIT_CUT){
        objectHierarchy->cutItems();
    }else if(event.GetId() == MENU_EDIT_PASTE){
        objectHierarchy->pasteItems();
    }else if(event.GetId() == MENU_EDIT_DELETE){
        objectHierarchy->deleteItems();
    }
}
