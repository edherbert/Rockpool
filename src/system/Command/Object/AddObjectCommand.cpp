#include "AddObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../../map/Object/MeshObject.h"
#include "../../../ui/Hierarchy/HierarchyTree.h"

AddObjectCommand::AddObjectCommand(const wxString &name, const wxString &path, HierarchyTree *tree, int parentItem, int index) : ObjectCommand(tree){
    this->path = path;
    this->name = path;
    this->parentItem = parentItem;
    this->index = index;

    setup();

    object = new MeshObject(tree->getMap()->getSceneManager(), name, path);
}

AddObjectCommand::AddObjectCommand(PrimativeIds primId, HierarchyTree *tree, int parentItem, int index) : ObjectCommand(tree){
    this->parentItem = parentItem;
    this->index = index;

    if(primId == PrimativeEmpty) name = "Empty";
    if(primId == PrimativeCube) name = "Cube";
    if(primId == PrimativeCone) name = "Cone";
    if(primId == PrimativeSphere) name = "Sphere";
    if(primId == PrimativePlane) name = "Plane";

    this->path = name + ".mesh";

    setup();

    if(primId == PrimativeEmpty){
        object = new Object(tree->getMap()->getSceneManager());
    }else{
        object = new MeshObject(tree->getMap()->getSceneManager(), name, this->path);
    }
}

AddObjectCommand::~AddObjectCommand(){

}

void AddObjectCommand::setup(){
    wxTreeItemId targetItem;
    if(parentItem == -1){
        targetItem = tree->GetRootItem();
    }else{
        targetItem = tree->getItem(parentItem);
    }
    if(index == -1){
        //If no index was provided (-1 is the default), then just insert it at the end
        index = tree->GetChildrenCount(targetItem, false);
    }
}

void AddObjectCommand::performAction(){
    wxTreeItemId targetItem;
    if(parentItem == -1){
        targetItem = tree->GetRootItem();
    }else{
        targetItem = tree->getItem(parentItem);
    }
    HierarchyObjectInformation *parentInfo = (HierarchyObjectInformation*)tree->GetItemData(targetItem);
    parentInfo->getObject()->addChild(object);

    HierarchyObjectInformation *info = new HierarchyObjectInformation(object);

    wxTreeItemId newItem = tree->InsertItem(targetItem, index, name, -1, -1, info);

    if(!ran){
        addedItem = tree->addItem(newItem);
    }else{
        tree->setItem(addedItem, newItem);
    }

    ran = true;
    tree->updateSelection();
}

void AddObjectCommand::performAntiAction(){
    if(addedItem != -1){
        tree->Delete(tree->getItem(addedItem));
        object->removeFromParent();
    }
    tree->updateSelection();
}
