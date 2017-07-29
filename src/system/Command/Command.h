#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

class Command
{
    public:
        Command();
        virtual ~Command();

        virtual void performAction();
        virtual void performAntiAction();
        virtual void cleanupTemporaryResources();

    protected:

    private:
};

#endif // COMMAND_H
