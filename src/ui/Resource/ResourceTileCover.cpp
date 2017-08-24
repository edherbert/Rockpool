#include "ResourceTileCover.h"

#include <wx/filename.h>

#include "ResourcePanel.h"
#include "ResourceTile.h"
#include "../MainFrame.h"
#include "../Hierarchy/ObjectHierarchy.h"
#include "../Hierarchy/HierarchyTree.h"

ResourceTileCover::ResourceTileCover(ResourcePanel *resPanel, ResourceTile *parent) : wxPanel(resPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 100)){
    this->resPanel = resPanel;
    this->parent = parent;

    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ResourceTileCover::mouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(ResourceTileCover::mouseUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(ResourceTileCover::mouseMoved));
}

ResourceTileCover::~ResourceTileCover(){

}

void ResourceTileCover::setId(int id){
    this->id = id;
}

void ResourceTileCover::mouseDown(wxMouseEvent &event){
    int x, y;
    GetPosition(&x, &y);
    resPanel->selectTile(id);
}

void ResourceTileCover::mouseMoved(wxMouseEvent &event){
    if(wxGetMouseState().LeftDown()){
        wxFileName name(parent->getValue());

        resPanel->beginDragAnim();
        resPanel->updateDragAnim();
        if(name.GetExt() == "mesh"){
            resPanel->getMainFrame()->getObjectHierarchy()->getTree()->beginResourceDrag(parent->getValue());
            resPanel->getMainFrame()->getObjectHierarchy()->getTree()->updateResourceDrag();
        }
    }
}

void ResourceTileCover::mouseUp(wxMouseEvent &event){
    resPanel->endDragAnim();

    resPanel->getMainFrame()->getObjectHierarchy()->getTree()->endResourceDrag();
}
