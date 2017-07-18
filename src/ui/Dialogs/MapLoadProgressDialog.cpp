#include "MapLoadProgressDialog.h"

MapLoadProgressDialog::MapLoadProgressDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, wxT("Loading Map"), wxDefaultPosition, wxSize(300, 100)){
    Centre();

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *gaugeSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);

    progressGauge = new wxGauge(this, wxID_ANY, 100);

    setValue(0);

    progressText = new wxStaticText(this, wxID_ANY, "Loading");

    textSizer->Add(progressText, 1, wxLEFT | wxRIGHT | wxTOP | wxTOP, 5);
    gaugeSizer->Add(progressGauge, 1, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 10);

    vertical->Add(textSizer, 1, wxLEFT | wxRIGHT | wxTOP | wxEXPAND, 5);
    vertical->Add(gaugeSizer, 1, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 10);

    SetSizer(vertical);

    Show();
}

MapLoadProgressDialog::~MapLoadProgressDialog(){

}

void MapLoadProgressDialog::setText(wxString text){
    progressText->SetLabel(text);
}

void MapLoadProgressDialog::setValue(int ammount){
    progressCount = ammount;
    progressGauge->SetValue(progressCount);
}

void MapLoadProgressDialog::addValue(int ammount){
    progressCount += ammount;
    progressGauge->SetValue(progressCount);
}
