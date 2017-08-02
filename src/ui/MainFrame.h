#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "wxIDs.h"

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

#include <wx/accel.h>

#include <wx/aui/aui.h>

class Main;
class ToolsPanel;
class ToolPreferencesHandler;
class RenderTimer;
class ToolsPanelHandler;
class TerrainInfoHandler;
class MapPropertiesDialog;
class ResourceBrowser;
class ResourceManager;

struct HandlerData{
    ToolPreferencesHandler *toolPreferencesHandler;
    ToolsPanelHandler *toolPanelHandler;
    TerrainInfoHandler *terrainInfoHandler;
};

class MainFrame : public wxFrame{
public:
	MainFrame(Main *main, const wxString &title);
	~MainFrame();

    Main* getMain();
    GLCanvas* getCanvas();

    wxMenuItem *showToolPreferences;
    wxMenuItem *showTerrainInfo;
    wxMenuItem *showTerrainToolbar;
    wxMenuItem *showResourceBrowser;

    ToolPreferencesHandler* getToolPreferencesHandler();
    TerrainInfoHandler* getTerrainInfoHandler();
    HandlerData* getHandlerData();
    ResourceManager* getResourceManager();
    ResourceBrowser* getResourceBrowser();

    DECLARE_EVENT_TABLE()

private:
	GLCanvas *canvas;
	Main *main;
	RenderTimer *timer;
	wxAuiManager *auiManager;

	ToolPreferencesHandler *toolPreferencesHandler;
	ToolsPanelHandler *toolPanelHandler;
	TerrainInfoHandler *terrainInfoHandler;
	ResourceBrowser *resourceBrowser;

	void setupMenuBar();

    void onMaximize(wxMaximizeEvent &event);

    void newMap(wxCommandEvent &event);
    void openMap(wxCommandEvent &event);
    void saveMap(wxCommandEvent &event);

    void openMapProperties(wxCommandEvent& event);

    void ShowToolPreferences(wxCommandEvent& event);
    void ShowTerrainToolbar(wxCommandEvent &event);
    void ShowTerrainInfo(wxCommandEvent &event);
    void ShowResourceBrowser(wxCommandEvent &event);

    void undoAction(wxCommandEvent &event);
    void redoAction(wxCommandEvent &event);

    void closeAUIPanel(wxAuiManagerEvent &event);

    HandlerData handlerData;
};

#endif
