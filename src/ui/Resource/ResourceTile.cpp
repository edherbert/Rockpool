#include "ResourceTile.h"

#include <wx/filename.h>

#include "ResourcePanel.h"
#include "../MainFrame.h"
#include "../Hierarchy/ObjectHierarchy.h"
#include "../Hierarchy/HierarchyTree.h"

ResourceTile::ResourceTile(wxWindow *parent, ResourcePanel *resPanel, wxBitmap *defaultBitmap) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(100, 100)){
    this->resPanel = resPanel;
    this->defaultBitmap = defaultBitmap;
    this->parent = parent;

    Connect(wxEVT_PAINT, wxPaintEventHandler(ResourceTile::paintTile));

    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ResourceTile::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ResourceTile::mouseUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(ResourceTile::mouseMoved));
}

ResourceTile::~ResourceTile(){

}

void ResourceTile::paintTile(wxPaintEvent &event){
    wxPaintDC dc(this);
    dc.Clear();

    dc.DrawBitmap(*defaultBitmap, 50 - (defaultBitmap->GetWidth() / 2), 0);
    dc.DrawText(currentLabel, wxPoint(0, 50));
}

void ResourceTile::setLabel(const wxString &l){
    wxSystemSettings settings;

    wxClientDC dc(this);
    dc.SetFont(settings.GetFont(wxSYS_SYSTEM_FONT));

    wxSize fontSize = dc.GetTextExtent(l);

    wxString newString = "";
    int stringThreshold = 90;
    for(int i = 0; i < l.size(); i++){
        if(dc.GetTextExtent(l.substr(0, i + 1)).GetWidth() >= stringThreshold){
            newString.Append("\n");
            newString.Append(l[i]);
            stringThreshold += 90;
        }else{
            newString.Append(l[i]);
        }
    }

    //label->SetLabel(newString);
    currentLabel = newString;
    currentValue = l;

    int height = 50 + dc.GetTextExtent(newString).GetHeight();
    if(height < 100){
        setSize(100, 100);
    }else{
        setSize(100, height + 10);
    }

    //Layout();
}

wxString ResourceTile::getLabel(){
    return currentLabel;
}

wxString ResourceTile::getValue(){
    return currentValue;
}

void ResourceTile::setId(int id){
    this->id = id;
}

int ResourceTile::getId(){
    return id;
}

void ResourceTile::setPosition(int x, int y){
    SetPosition(wxPoint(x, y));
}

void ResourceTile::setSize(int width, int height){
    SetSize(width, height);
}

void ResourceTile::selectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_WINDOW));
}

void ResourceTile::deSelectTile(){
    wxSystemSettings settings;
    SetBackgroundColour(settings.GetColour(wxSYS_COLOUR_MENU));
}

wxSize ResourceTile::getSize(){
    return GetSize();
}

void ResourceTile::mouseDown(wxMouseEvent &event){
    resPanel->selectTile(getId());
}

void ResourceTile::mouseMoved(wxMouseEvent &event){
    if(wxGetMouseState().LeftDown()){
        wxFileName name(getValue());

        resPanel->beginDragAnim();
        resPanel->updateDragAnim();
        if(name.GetExt() == "mesh"){
            resPanel->getMainFrame()->getObjectHierarchy()->getTree()->beginResourceDrag(getValue());
            resPanel->getMainFrame()->getObjectHierarchy()->getTree()->updateResourceDrag();
        }
    }
}

void ResourceTile::mouseUp(wxMouseEvent &event){
    resPanel->endDragAnim();

    resPanel->getMainFrame()->getObjectHierarchy()->getTree()->endResourceDrag();
}
