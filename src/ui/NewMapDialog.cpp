#include "NewMapDialog.h"

NewMapDialog::NewMapDialog(MainFrame *parent, Main *main) : wxDialog(parent, wxID_ANY, wxT("New Map"), wxDefaultPosition, wxSize(400, 450)){
    this->main = main;
    this->parent = parent;
    Centre();

    //Start layout
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer *newMapVerticalSizer = new wxBoxSizer(wxVERTICAL);


    //Contents of the map data box
    wxStaticBox *mapData = new wxStaticBox(panel, wxID_ANY, wxT("Map Data"));

    wxBoxSizer *mapDataHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer *flexMapData = new wxFlexGridSizer(3, 2, 9, 25);

    wxStaticText *mapNameText = new wxStaticText(mapData, wxID_ANY, wxT("Map Name"));
    wxStaticText *mapWidthText = new wxStaticText(mapData, wxID_ANY, wxT("Map Width"));
    wxStaticText *mapHeightText = new wxStaticText(mapData, wxID_ANY, wxT("Map Height"));

    mapNameControl = new wxTextCtrl(mapData, NEW_MAP_DIALOG_MAP_NAME_CONTROL);
    mapWidthSpin = new wxSpinCtrl(mapData, NEW_MAP_DIALOG_MAP_WIDTH_SPIN);
    mapHeightSpin = new wxSpinCtrl(mapData, NEW_MAP_DIALOG_MAP_HEIGHT_SPIN);

    mapNameControl->SetValue("New Map");
    mapWidthSpin->SetRange(1, 1000);
    mapHeightSpin->SetRange(1, 1000);

    mapWidthSpin->SetValue(1);
    mapHeightSpin->SetValue(1);

    flexMapData->Add(mapNameText);
    flexMapData->Add(mapNameControl, 1, wxEXPAND);
    flexMapData->Add(mapWidthText);
    flexMapData->Add(mapWidthSpin, 1);
    flexMapData->Add(mapHeightText);
    flexMapData->Add(mapHeightSpin, 1);

    flexMapData->AddGrowableCol(1, 1);

    mapDataHorizontal->Add(flexMapData, 1, wxALL | wxEXPAND, 15);

    mapData->SetSizer(mapDataHorizontal);


    //Terrain data section
    wxStaticBox *terrainData = new wxStaticBox(panel, wxID_ANY, wxT("Terrain Data"));

    wxBoxSizer *terrainDataHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer *flexTerrainData = new wxFlexGridSizer(3, 2, 9, 25);

    wxStaticText *vertexCountText = new wxStaticText(terrainData, wxID_ANY, wxT("Vertex Count"));
    wxStaticText *terrainSizeText = new wxStaticText(terrainData, wxID_ANY, wxT("Terrain Size"));
    wxStaticText *terrainHeightText = new wxStaticText(terrainData, wxID_ANY, wxT("Terrain Height"));

    wxArrayString items;
    items.Add("65");
    items.Add("129");
    items.Add("257");
    items.Add("513");
    vertexCountBox = new wxComboBox(terrainData, NEW_MAP_DIALOG_TERRAIN_VERTEX_COUNT_BOX, "513", wxDefaultPosition, wxDefaultSize, items, wxCB_READONLY);
    terrainSizeSpin = new wxSpinCtrl(terrainData, NEW_MAP_DIALOG_TERRAIN_SIZE_SPIN);
    terrainHeightSpin = new wxSpinCtrl(terrainData, NEW_MAP_DIALOG_TERRAIN_HEIGHT_SPIN);

    terrainSizeSpin->SetRange(1, 100000);
    terrainHeightSpin->SetRange(1, 10000);

    //vertexCountSpin->SetValue(513);
    terrainSizeSpin->SetValue(6000);
    terrainHeightSpin->SetValue(600);

    flexTerrainData->Add(vertexCountText);
    //flexTerrainData->Add(vertexCountSpin);
    flexTerrainData->Add(vertexCountBox);
    flexTerrainData->Add(terrainSizeText);
    flexTerrainData->Add(terrainSizeSpin);
    flexTerrainData->Add(terrainHeightText);
    flexTerrainData->Add(terrainHeightSpin);

    terrainDataHorizontal->Add(flexTerrainData, 1, wxALL | wxEXPAND, 15);
    terrainData->SetSizer(terrainDataHorizontal);



    wxBoxSizer *newMapButtonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *ok = new wxButton(panel, NEW_MAP_OK, wxT("Ok"));
    wxButton *cancel = new wxButton(panel, NEW_MAP_CANCEL, wxT("Cancel"));

    newMapButtonSizer->Add(ok);
    newMapButtonSizer->Add(cancel, 0, wxLEFT, 10);


    newMapVerticalSizer->Add(mapData, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 10);
    newMapVerticalSizer->Add(terrainData, 1, wxEXPAND | wxALL, 10);

    newMapVerticalSizer->Add(newMapButtonSizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
    panel->SetSizer(newMapVerticalSizer);


    Connect(NEW_MAP_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewMapDialog::OKPressed));
    Connect(NEW_MAP_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewMapDialog::CancelPressed));

    ShowModal();
}

NewMapDialog::~NewMapDialog(){

}

void NewMapDialog::OKPressed(wxCommandEvent& WXUNUSED(event)){
    wxDirDialog *dirDialog = new wxDirDialog(this);
    if(dirDialog->ShowModal() != wxID_CANCEL){

        //Get the values from the various things.
        wxString path = dirDialog->GetPath();

        mapInformation info;
        info.mapName = mapNameControl->GetValue();
        info.mapWidth = mapWidthSpin->GetValue();
        info.mapHeight = mapHeightSpin->GetValue();

        info.vertexCount = wxAtoi(vertexCountBox->GetValue());
        info.terrainSize = terrainSizeSpin->GetValue();
        info.terrainHeight = terrainHeightSpin->GetValue();

        main->createMap(parent, path, info);
    }
    Destroy();
}

void NewMapDialog::CancelPressed(wxCommandEvent& WXUNUSED(event)){
    Destroy();
}
