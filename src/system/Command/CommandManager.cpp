#include "CommandManager.h"

CommandManager::CommandManager(MainFrame *mainFrame){
    this->mainFrame = mainFrame;
}

CommandManager::~CommandManager(){

}

void CommandManager::pushCommand(Command *com){
    com->cleanupTemporaryResources();
    pastCommands.push_back(com);

    futureCommands.clear();
}

//The back of the past list is the most recent command.
//The back of the recent list is the most recent command.
//So re-doing commands would involve taking the back command from the future list and moving it to the back of the past list.
void CommandManager::undoLastCommand(){
    if(pastCommands.size() <= 0) return;
    pastCommands.at(pastCommands.size() - 1)->performAntiAction();

    futureCommands.push_back(pastCommands.at(pastCommands.size() - 1));
    pastCommands.pop_back();

    mainFrame->getCanvas()->renderFrame();
}

void CommandManager::redoLastCommand(){
    if(futureCommands.size() <= 0) return;
    futureCommands.at(futureCommands.size() - 1)->performAction();

    pastCommands.push_back(futureCommands.at(futureCommands.size() - 1));
    futureCommands.pop_back();

    mainFrame->getCanvas()->renderFrame();
}

//updates the object functions with their new item ids
void CommandManager::updateObjectCommands(wxTreeItemId oldId, wxTreeItemId newId){
    for(Command* i : pastCommands){
        if(i->getType() == objectCommand){
            ObjectCommand *command = (ObjectCommand*)i;
            command->checkParent(oldId, newId);
        }
    }
    for(Command* i : futureCommands){
        if(i->getType() == objectCommand){
            ObjectCommand *command = (ObjectCommand*)i;
            command->checkParent(oldId, newId);
        }
    }
}
