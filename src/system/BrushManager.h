#ifndef BRUSHMANAGER_H
#define BRUSHMANAGER_H

#include "../map/Main.h"

class BrushManager
{
    public:
        BrushManager(Main *main);
        virtual ~BrushManager();

        void getCurrentBrushData();

    protected:

    private:
};

#endif // BRUSHMANAGER_H
