#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "../../ui/MainFrame.h"

#include "TerrainEditCommand.h"

class TerrainEditCommand;

class CommandManager
{
    public:
        CommandManager(MainFrame *mainFrame);
        virtual ~CommandManager();

        void undoLastCommand();
        void redoLastCommand();

        void pushCommand(Command *com);

    protected:

    private:
        MainFrame *mainFrame;

        std::vector<Command*>pastCommands;
        std::vector<Command*>futureCommands;
};

#endif // COMMANDMANAGER_H
