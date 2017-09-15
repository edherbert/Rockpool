#include "MapPropertiesDialog.h"

#include "../wxIDs.h"
#include "../../map/Main.h"
#include "../Resource/ResourceBrowser.h"
#include "../../system/ResourceManager.h"

#include "MapPropertiesSkyBoxDialog.h"

#include <Ogre.h>

MapPropertiesDialog::MapPropertiesDialog(MainFrame *mainFrame, wxWindow *parent) : wxDialog(parent, wxID_ANY, wxT("Map Properties"), wxDefaultPosition, wxSize(700, 600)){
    this->mainFrame = mainFrame;

    wxNotebook *nb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

    wxPanel *mapInformationPanel = new wxPanel(nb);
    wxPanel *mapAttributesPanel = new wxPanel(nb);
    wxPanel *skyBoxesPanel = new wxPanel(nb);
    wxPanel *resourceLocationsPanel = new wxPanel(nb);

    setupMapProperties(mapInformationPanel);
    setupSkyBoxProperties(skyBoxesPanel);
    setupResourceLocationProperties(resourceLocationsPanel);

    nb->AddPage(mapInformationPanel, wxT("Map Information"));
    nb->AddPage(mapAttributesPanel, wxT("Map Attributes"));
    nb->AddPage(skyBoxesPanel, wxT("Skyboxes"));
    nb->AddPage(resourceLocationsPanel, wxT("Resource Locations"));

    nb->SetSelection(2);

    wxBoxSizer *graphicSettingsBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_ADD, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesAddLocation));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_EDIT, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesEditLocationCallback));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_DELETE, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesDeleteLocation));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_LIST, wxEVT_LISTBOX_DCLICK, wxCommandEventHandler(MapPropertiesDialog::doubleClickResourceList));

    Connect(MAP_PROPERTIES_DIALOG_SKYBOX_ADD, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::addSkybox));
    Connect(MAP_PROPERTIES_DIALOG_SKYBOX_DELETE, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::deletekybox));
    Connect(MAP_PROPERTIES_DIALOG_SKYBOX_EDIT, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::editSkybox));

    ShowModal();
}

MapPropertiesDialog::~MapPropertiesDialog(){

}

void MapPropertiesDialog::setupMapProperties(wxPanel *parent){

}

void MapPropertiesDialog::setupResourceLocationProperties(wxPanel *parent){
    resourceLocationsList = new wxListBox(parent, MAP_PROPERTIES_DIALOG_RESOURCES_LIST);
    resourceLocationsList->Set(mainFrame->getMain()->getResourceListItems());

    wxBoxSizer *resourceLocationsPanelSizer = new wxBoxSizer(wxVERTICAL);

    wxButton *newLocationButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_RESOURCES_ADD, wxT("Add Location"));
    wxButton *editLocationButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_RESOURCES_EDIT, wxT("Edit Location"));
    wxButton *deleteLocationButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_RESOURCES_DELETE, wxT("Delete Location"));

    wxBoxSizer *resourceLocationsPanelHorizontal = new wxBoxSizer(wxHORIZONTAL);
    resourceLocationsPanelHorizontal->Add(newLocationButton, 0, wxALL, 10);
    resourceLocationsPanelHorizontal->Add(editLocationButton, 0, wxRIGHT | wxTOP | wxBOTTOM, 10);
    resourceLocationsPanelHorizontal->Add(new wxPanel(parent), 1, wxEXPAND);
    resourceLocationsPanelHorizontal->Add(deleteLocationButton, 0, wxEXPAND | wxALL, 10);

    resourceLocationsPanelSizer->Add(resourceLocationsList, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    resourceLocationsPanelSizer->Add(resourceLocationsPanelHorizontal, 0, wxEXPAND);

    parent->SetSizer(resourceLocationsPanelSizer);
}

void MapPropertiesDialog::setupSkyBoxProperties(wxPanel *parent){
    skyBoxList = new wxListBox(parent, MAP_PROPERTIES_DIALOG_SKYBOX_LIST);

    wxBoxSizer *skyBoxBoxSizer = new wxBoxSizer(wxVERTICAL);

    wxButton *newItemButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_SKYBOX_ADD, wxT("Add SkyBox"));
    wxButton *editItemButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_SKYBOX_EDIT, wxT("Edit SkyBox"));
    wxButton *deleteItemButton = new wxButton(parent, MAP_PROPERTIES_DIALOG_SKYBOX_DELETE, wxT("Delete SkyBox"));

    wxBoxSizer *SkyBoxPanelHorizontal = new wxBoxSizer(wxHORIZONTAL);
    SkyBoxPanelHorizontal->Add(newItemButton, 0, wxALL, 10);
    SkyBoxPanelHorizontal->Add(editItemButton, 0, wxRIGHT | wxTOP | wxBOTTOM, 10);
    SkyBoxPanelHorizontal->Add(new wxPanel(parent), 1, wxEXPAND);
    SkyBoxPanelHorizontal->Add(deleteItemButton, 0, wxEXPAND | wxALL, 10);

    skyBoxBoxSizer->Add(skyBoxList, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    skyBoxBoxSizer->Add(SkyBoxPanelHorizontal, 0, wxEXPAND);

    parent->SetSizer(skyBoxBoxSizer);
}

void MapPropertiesDialog::resourcesAddLocation(wxCommandEvent &event){
    wxDirDialog *dialog = new wxDirDialog(this, "Select a directory.", mainFrame->getMain()->getProjectDirectory());
    if(dialog->ShowModal() != wxID_CANCEL){
        wxFileName dir(dialog->GetPath());

        wxString projectDirectory = mainFrame->getMain()->getProjectDirectory();
        if(projectDirectory != wxEmptyString){
            dir.MakeRelativeTo(projectDirectory);
        }

        for(int i = 0; i < resourceLocationsList->GetCount(); i++){
            if(resourceLocationsList->GetString(i) == dir.GetFullPath()){
                wxMessageDialog dialog(this, wxT("That resource location is already in use!"), wxT("Error"));
                dialog.ShowModal();
                return;
            }
        }

        Ogre::String pathToAdd = (Ogre::String)(mainFrame->getMain()->getProjectDirectory() + "/" + dir.GetFullPath());
        if(mainFrame->getMain()->addResourceLocation(pathToAdd)){
            //If the resource location was added successfully
            resourceLocationsList->Append(dir.GetFullPath());

            mainFrame->getResourceManager()->checkResourceLocations();
            mainFrame->getResourceBrowser()->updateTiles();
            mainFrame->getResourceBrowser()->layoutTiles();
        }
    }
}

void MapPropertiesDialog::resourcesEditLocation(){
    if(resourceLocationsList->GetSelection() == wxNOT_FOUND) return;

    //Get the path to the directory that should be changed, so that the browser can open on it
    int selection = resourceLocationsList->GetSelection();
    wxString current = resourceLocationsList->GetString(selection);
    wxString path = mainFrame->getMain()->getProjectDirectory() + "/" + current;

    wxDirDialog *dialog = new wxDirDialog(this, "Select a directory.", path);
    if(dialog->ShowModal() != wxID_CANCEL){

        wxFileName dir(dialog->GetPath());
        wxString projectDirectory = mainFrame->getMain()->getProjectDirectory();
        //If there is a project directory, then make the paths point from it, rather than their paths from the root
        if(projectDirectory != wxEmptyString){
            dir.MakeRelativeTo(projectDirectory);
        }

        if(current == dir.GetFullPath()){
            return;
        }

        //The path from the root directory to this new one
        wxString longPath = mainFrame->getMain()->getProjectDirectory() + "/" + dir.GetFullPath();
        //If the resource location cannot be added, then don't do anything.
        if(!mainFrame->getMain()->addResourceLocation(longPath, true, selection)) return;
        mainFrame->getMain()->removeResourceLocation(path);

        resourceLocationsList->Delete(selection);
        resourceLocationsList->Insert(dir.GetFullPath(), selection);
        resourceLocationsList->SetSelection(selection);

        mainFrame->getResourceManager()->checkResourceLocations();
        mainFrame->getResourceBrowser()->updateTiles();
        mainFrame->getResourceBrowser()->layoutTiles();
    }
}

void MapPropertiesDialog::resourcesEditLocationCallback(wxCommandEvent &event){
    resourcesEditLocation();
}

void MapPropertiesDialog::resourcesDeleteLocation(wxCommandEvent &event){
    if(resourceLocationsList->GetSelection() == wxNOT_FOUND) return;

    int selection = resourceLocationsList->GetSelection();
    wxString current = resourceLocationsList->GetString(selection);
    wxString path = mainFrame->getMain()->getProjectDirectory() + "/" + current;
    resourceLocationsList->Delete(selection);

    mainFrame->getMain()->removeResourceLocation(path);

    mainFrame->getResourceManager()->checkResourceLocations();
    mainFrame->getResourceBrowser()->updateTiles();
    mainFrame->getResourceBrowser()->layoutTiles();
}

void MapPropertiesDialog::doubleClickResourceList(wxCommandEvent &event){
    resourcesEditLocation();
}


void MapPropertiesDialog::addSkybox(wxCommandEvent &event){
    //MapPropertiesSkyBoxDialog dialog(this);
    MapPropertiesSkyBoxDialog *dialog = new MapPropertiesSkyBoxDialog(this);
}

void MapPropertiesDialog::editSkybox(wxCommandEvent &event){
    std::cout << "Edit" << std::endl;
}

void MapPropertiesDialog::deletekybox(wxCommandEvent &event){
    std::cout << "Delete" << std::endl;
}

MainFrame* MapPropertiesDialog::getMainFrame(){
    return mainFrame;
}
