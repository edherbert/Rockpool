#ifndef PASTEOBJECTCOMMAND_H
#define PASTEOBJECTCOMMAND_H

#include "ObjectCommand.h"

class HierarchyTree;
class HierarchyClipboardManager;

class PasteObjectCommand : public ObjectCommand
{
    public:
        PasteObjectCommand(HierarchyTree *tree, HierarchyClipboardManager *clipboardManager, int destinationId);
        virtual ~PasteObjectCommand();

        void performAction();
        void performAntiAction();

    protected:

    private:
        HierarchyClipboardManager *clipboardManager;
        int destinationId;
};

#endif // PASTEOBJECTCOMMAND_H
