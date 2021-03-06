#include "ObjectHierarchy.h"

#include <wx/panel.h>
#include <wx/aui/aui.h>
#include <wx/menuitem.h>

#include "../../system/Command/Object/DeleteObjectCommand.h"
#include "../../system/Command/Object/PasteObjectCommand.h"
#include "../../system/Command/CommandManager.h"
#include "../../system/HierarchyClipboardManager.h"
#include "../../map/Main.h"

ObjectHierarchy::ObjectHierarchy(MainFrame *mainFrame, wxAuiManager *auiManager) : wxPanel(mainFrame){
    this->mainFrame = mainFrame;
    this->auiManager = auiManager;

    wxAuiPaneInfo info;
    info.Caption(wxT("Object Hierarchy"));
    info.Left();
    info.BestSize(wxSize(300, 400));
    info.Show(true);
    info.Name(wxT("ObjectHierarchy"));
    auiManager->AddPane(this, info);

    wxBoxSizer *vertical = new wxBoxSizer(wxVERTICAL);
    tree = new HierarchyTree(this);

    vertical->Add(tree, 1, wxEXPAND);

    SetSizer(vertical);

    setObjectHierarchyVisible(false);
}

ObjectHierarchy::~ObjectHierarchy(){

}

void ObjectHierarchy::setObjectHierarchyVisible(bool visible){
    if(visible){
        auiManager->GetPane(wxT("ObjectHierarchy")).Show();
        mainFrame->showObjectHierarchy->Check(true);
    }else{
        auiManager->GetPane(wxT("ObjectHierarchy")).Hide();
        mainFrame->showObjectHierarchy->Check(false);
    }
    auiManager->Update();
    hierarchyVisible = visible;
}

void ObjectHierarchy::setMap(Map *map){
    tree->setMap(map);
}

MainFrame* ObjectHierarchy::getMainFrame(){
    return mainFrame;
}

HierarchyTree* ObjectHierarchy::getTree(){
    return tree;
}

bool ObjectHierarchy::checkSelectionExists(){
    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    if(items.size() <= 0) return false;
    else return true;
}

void ObjectHierarchy::copyItems(){
    if(!checkSelectionExists()) return;

    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    tree->getClipboardManager()->copyItems(items);
}

void ObjectHierarchy::cutItems(){
    if(!checkSelectionExists()) return;

    copyItems();
    deleteItems();
}

void ObjectHierarchy::pasteItems(){
    if(!tree->getClipboardManager()->containsItems()) return;

    //Get the destination of the items
    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    //If there are no items in the list, then append to the root item.
    int destinationId = -1;
    if(items.size() > 0){
        //If there is a multiple selection, then just set the destination to the first item.
        destinationId = tree->getId(items[0]);
    }

    //Put the actual destination in here at some point
    PasteObjectCommand *pasteCommand = new PasteObjectCommand(tree, tree->getClipboardManager(), destinationId);
    pasteCommand->performAction();

    getMainFrame()->getMain()->getCommandManager()->pushCommand(pasteCommand);
}

void ObjectHierarchy::deleteItems(){
    if(!checkSelectionExists()) return;

    wxArrayTreeItemIds items;
    tree->GetSelections(items);

    DeleteObjectCommand *deleteCommand = new DeleteObjectCommand(tree, items);
    deleteCommand->performAction();

    getMainFrame()->getMain()->getCommandManager()->pushCommand(deleteCommand);
}
