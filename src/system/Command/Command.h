#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

enum commandType{
    terrainCommand,
    objectCommand,
};

class Command
{
    public:
        Command();
        virtual ~Command();

        virtual void performAction();
        virtual void performAntiAction();
        virtual void cleanupTemporaryResources();

        commandType getType();

    protected:
        commandType type;

    private:
};

#endif // COMMAND_H
