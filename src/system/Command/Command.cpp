#include "Command.h"

Command::Command(){

}

Command::~Command(){

}

void Command::performAction(){

}

void Command::performAntiAction(){

}

void Command::cleanupTemporaryResources(){

}

commandType Command::getType(){
    return type;
}
