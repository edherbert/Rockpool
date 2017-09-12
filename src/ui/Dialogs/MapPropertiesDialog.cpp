#include "MapPropertiesDialog.h"

#include "../wxIDs.h"
#include "../../map/Main.h"
#include "../Resource/ResourceBrowser.h"
#include "../../system/ResourceManager.h"

#include <Ogre.h>

MapPropertiesDialog::MapPropertiesDialog(MainFrame *mainFrame, wxWindow *parent) : wxDialog(parent, wxID_ANY, wxT("Map Properties"), wxDefaultPosition, wxSize(700, 600)){
    this->mainFrame = mainFrame;

    wxNotebook *nb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

    wxPanel *mapInformationPanel = new wxPanel(nb);
    wxPanel *mapAttributesPanel = new wxPanel(nb);
    wxPanel *skyboxesPanel = new wxPanel(nb);
    wxPanel *resourceLocationsPanel = new wxPanel(nb);

    setupMapProperties(mapInformationPanel);

    list = new wxListBox(resourceLocationsPanel, 706);
    list->Set(mainFrame->getMain()->getResourceListItems());

    wxBoxSizer *resourceLocationsPanelSizer = new wxBoxSizer(wxVERTICAL);

    wxButton *newLocationButton = new wxButton(resourceLocationsPanel, MAP_PROPERTIES_DIALOG_RESOURCES_ADD, wxT("Add Location"));
    wxButton *editLocationButton = new wxButton(resourceLocationsPanel, MAP_PROPERTIES_DIALOG_RESOURCES_EDIT, wxT("Edit Location"));
    wxButton *deleteLocationButton = new wxButton(resourceLocationsPanel, MAP_PROPERTIES_DIALOG_RESOURCES_DELETE, wxT("Delete Location"));

    wxBoxSizer *resourceLocationsPanelHorizontal = new wxBoxSizer(wxHORIZONTAL);
    resourceLocationsPanelHorizontal->Add(newLocationButton, 0, wxALL, 10);
    resourceLocationsPanelHorizontal->Add(editLocationButton, 0, wxRIGHT | wxTOP | wxBOTTOM, 10);
    resourceLocationsPanelHorizontal->Add(new wxPanel(resourceLocationsPanel), 1, wxEXPAND);
    resourceLocationsPanelHorizontal->Add(deleteLocationButton, 0, wxEXPAND | wxALL, 10);

    //resourceLocationsPanelSizer->Add(listSizerBox, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    resourceLocationsPanelSizer->Add(list, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    resourceLocationsPanelSizer->Add(resourceLocationsPanelHorizontal, 0, wxEXPAND);

    resourceLocationsPanel->SetSizer(resourceLocationsPanelSizer);


    nb->AddPage(mapInformationPanel, wxT("Map Information"));
    nb->AddPage(mapAttributesPanel, wxT("Map Attributes"));
    nb->AddPage(skyboxesPanel, wxT("Skyboxes"));
    nb->AddPage(resourceLocationsPanel, wxT("Resource Locations"));

    //nb->SetSelection(2);

    wxBoxSizer *graphicSettingsBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_ADD, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesAddLocation));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_EDIT, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesEditLocationCallback));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_DELETE, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesDeleteLocation));

    Connect(706, wxEVT_LISTBOX_DCLICK, wxCommandEventHandler(MapPropertiesDialog::doubleClickResourceList));

    ShowModal();
}

MapPropertiesDialog::~MapPropertiesDialog(){

}

void MapPropertiesDialog::setupMapProperties(wxPanel *parent){

}

void MapPropertiesDialog::resourcesAddLocation(wxCommandEvent &event){
    wxDirDialog *dialog = new wxDirDialog(this, "Select a directory.", mainFrame->getMain()->getProjectDirectory());
    if(dialog->ShowModal() != wxID_CANCEL){
        wxFileName dir(dialog->GetPath());

        wxString projectDirectory = mainFrame->getMain()->getProjectDirectory();
        if(projectDirectory != wxEmptyString){
            dir.MakeRelativeTo(projectDirectory);
        }

        for(int i = 0; i < list->GetCount(); i++){
            if(list->GetString(i) == dir.GetFullPath()){
                wxMessageDialog dialog(this, wxT("That resource location is already in use!"), wxT("Error"));
                dialog.ShowModal();
                return;
            }
        }

        Ogre::String pathToAdd = (Ogre::String)(mainFrame->getMain()->getProjectDirectory() + "/" + dir.GetFullPath());
        if(mainFrame->getMain()->addResourceLocation(pathToAdd)){
            //If the resource location was added successfully
            list->Append(dir.GetFullPath());

            mainFrame->getResourceManager()->checkResourceLocations();
            mainFrame->getResourceBrowser()->updateTiles();
            mainFrame->getResourceBrowser()->layoutTiles();
        }
    }
}

void MapPropertiesDialog::resourcesEditLocation(){
    if(list->GetSelection() == wxNOT_FOUND) return;

    //Get the path to the directory that should be changed, so that the browser can open on it
    int selection = list->GetSelection();
    wxString current = list->GetString(selection);
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

        list->Delete(selection);
        list->Insert(dir.GetFullPath(), selection);
        list->SetSelection(selection);

        mainFrame->getResourceManager()->checkResourceLocations();
        mainFrame->getResourceBrowser()->updateTiles();
        mainFrame->getResourceBrowser()->layoutTiles();
    }
}

void MapPropertiesDialog::resourcesEditLocationCallback(wxCommandEvent &event){
    resourcesEditLocation();
}

void MapPropertiesDialog::resourcesDeleteLocation(wxCommandEvent &event){
    if(list->GetSelection() == wxNOT_FOUND) return;

    int selection = list->GetSelection();
    wxString current = list->GetString(selection);
    wxString path = mainFrame->getMain()->getProjectDirectory() + "/" + current;
    list->Delete(selection);

    mainFrame->getMain()->removeResourceLocation(path);

    mainFrame->getResourceManager()->checkResourceLocations();
    mainFrame->getResourceBrowser()->updateTiles();
    mainFrame->getResourceBrowser()->layoutTiles();
}

void MapPropertiesDialog::doubleClickResourceList(wxCommandEvent &event){
    resourcesEditLocation();
}
