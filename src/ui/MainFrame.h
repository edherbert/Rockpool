#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/aui/aui.h>

class Main;
class GLCanvas;
class ToolPreferencesHandler;
class RenderTimer;
class ToolsPanelHandler;
class TerrainInfoHandler;
class ResourceBrowser;
class ResourceManager;
class ObjectHierarchy;

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
    wxMenuItem *showObjectHierarchy;

    ToolPreferencesHandler* getToolPreferencesHandler();
    TerrainInfoHandler* getTerrainInfoHandler();
    HandlerData* getHandlerData();
    ResourceManager* getResourceManager();
    ResourceBrowser* getResourceBrowser();
    ObjectHierarchy* getObjectHierarchy();

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
	ObjectHierarchy *objectHierarchy;

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
    void ShowObjectHierarchy(wxCommandEvent &event);

    void clipboardAction(wxCommandEvent &event);

    void undoAction(wxCommandEvent &event);
    void redoAction(wxCommandEvent &event);

    void AUIPanelClosed(wxAuiManagerEvent &event);

    HandlerData handlerData;
};

#endif
