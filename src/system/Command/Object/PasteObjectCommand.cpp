#include "PasteObjectCommand.h"

#include "../../../ui/Hierarchy/HierarchyTree.h"
#include "../../../ui/Hierarchy/HierarchyObjectInformation.h"
#include "../../HierarchyClipboardManager.h"

PasteObjectCommand::PasteObjectCommand(HierarchyTree *tree, HierarchyClipboardManager *clipboardManager, int destinationId) : ObjectCommand(tree){
    this->clipboardManager = clipboardManager;

    if(!clipboardManager->containsItems()) return;

    std::vector<copyInfo> &info = clipboardManager->getItems();

    for(int i = 0; i < info.size(); i++){
        itemInfo[i].text = info[i].text;
        itemInfo[i].id = info[i].id;
        itemInfo[i].parentId = info[i].parentId;

        //Look into creating a function for the thing that finds the item type
        //finalise all this nonsense.
    }
}

PasteObjectCommand::~PasteObjectCommand(){

}

void PasteObjectCommand::performAction(){
    //Copy the contents of the clipboard into new items
    //Append them the same as any other item function.
    //Copy the items in the constructor

}

void PasteObjectCommand::performAntiAction(){

}
