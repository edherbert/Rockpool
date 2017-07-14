#include "MapPropertiesDialog.h"

MapPropertiesDialog::MapPropertiesDialog(wxWindow *parent) : wxDialog(parent, wxID_ANY, wxT("Map Properties"), wxDefaultPosition, wxSize(700, 600)){
    wxNotebook *nb = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

    wxPanel *mapInformationPanel = new wxPanel(nb);
    wxPanel *mapAttributesPanel = new wxPanel(nb);
    wxPanel *resourceLocationsPanel = new wxPanel(nb);

    wxSystemSettings settings;
    mapInformationPanel->SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_LISTBOX));

    list = new wxListBox(resourceLocationsPanel, wxID_ANY);

    wxArrayString strings;
    strings.Add("1111111111jfklsdjfkldsjflksjdlakf");
    strings.Add("2222222222jfklsdjfkldsjflksjdlakf");
    strings.Add("3333333333jfklsdjfkldsjflksjdlakf");
    strings.Add("4444444444jfklsdjfkldsjflksjdlakf");
    strings.Add("5555555555jfklsdjfkldsjflksjdlakf");
    strings.Add("6666666666jfklsdjfkldsjflksjdlakf");



    list->InsertItems(strings, 0);

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
    nb->AddPage(resourceLocationsPanel, wxT("Resource Locations"));

    nb->SetSelection(2);

    wxBoxSizer *graphicSettingsBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_ADD, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesAddLocation));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_EDIT, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesEditLocation));
    Connect(MAP_PROPERTIES_DIALOG_RESOURCES_DELETE, wxEVT_BUTTON, wxCommandEventHandler(MapPropertiesDialog::resourcesDeleteLocation));

    ShowModal();
}

MapPropertiesDialog::~MapPropertiesDialog(){

}

void MapPropertiesDialog::resourcesAddLocation(wxCommandEvent &event){
    wxDirDialog *dialog = new wxDirDialog(this, "Select a directory.");
    if(dialog->ShowModal() != wxID_CANCEL){
        list->Append(dialog->GetPath());
    }
}

void MapPropertiesDialog::resourcesEditLocation(wxCommandEvent &event){
    wxDirDialog *dialog = new wxDirDialog(this, "Select a directory.");
    if(dialog->ShowModal() != wxID_CANCEL){
        int selection = list->GetSelection();
        list->Delete(selection);
        list->Insert(dialog->GetPath(), list->GetSelection());
        list->SetSelection(selection);
    }
}

void MapPropertiesDialog::resourcesDeleteLocation(wxCommandEvent &event){
    list->Delete(list->GetSelection());
}
