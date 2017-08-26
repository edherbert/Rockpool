#include "HierarchyClipboardManager.h"

#include "../ui/Hierarchy/HierarchyTree.h"

HierarchyClipboardManager::HierarchyClipboardManager(HierarchyTree *tree){
    this->tree = tree;
}

HierarchyClipboardManager::~HierarchyClipboardManager(){

}

void HierarchyClipboardManager::copyItems(const wxArrayTreeItemIds &items){
    std::cout << "copying items" << std::endl;
}

void HierarchyClipboardManager::clearClipboard(){

}
