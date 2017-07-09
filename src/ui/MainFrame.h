#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "wxIDs.h"

#include "GLCanvas.h"
//#include "Tools/ToolsPanel.h"
#include "BottomPanel.h"
#include "../map/Main.h"
#include "NewMapDialog.h"
#include "RenderTimer.h"
#include "Tools/ToolPreferencesHandler.h"
#include "Tools/ToolsPanelHandler.h"
#include "TerrainInfoHandler.h"

#include <wx/aui/aui.h>

class Main;
class ToolsPanel;
class ToolPreferencesHandler;
class RenderTimer;
class ToolsPanelHandler;
class TerrainInfoHandler;

struct HandlerData{
    ToolPreferencesHandler *toolPreferencesHandler;
    ToolsPanelHandler *toolPanelHandler;
    TerrainInfoHandler *terrainInfoHandler;
};

class MainFrame : public wxFrame{
public:
	MainFrame(Main *main, const wxString &title);
	~MainFrame();

    void NewMap(wxCommandEvent& WXUNUSED(event));
    void OpenMap(wxCommandEvent& WXUNUSED(event));

    void ShowToolPreferences(wxCommandEvent& event);
    void ShowTerrainToolbar(wxCommandEvent &event);
    void ShowTerrainInfo(wxCommandEvent &event);

    wxMenuItem *showToolPreferences;
    wxMenuItem *showTerrainInfo;
    wxMenuItem *showTerrainToolbar;

    void closeToolPreferences(wxAuiManagerEvent &event);

    ToolPreferencesHandler* getToolPreferencesHandler();
    TerrainInfoHandler* getTerrainInfoHandler();
    HandlerData* getHandlerData();

    DECLARE_EVENT_TABLE()

private:
	GLCanvas *canvas;
	Main *main;
	RenderTimer *timer;
	wxAuiManager *auiManager;

	ToolPreferencesHandler *toolPreferencesHandler;
	ToolsPanelHandler *toolPanelHandler;
	TerrainInfoHandler *terrainInfoHandler;

	void setupMenuBar();

    void onMaximize(wxMaximizeEvent &event);

    HandlerData handlerData;
};

#endif
