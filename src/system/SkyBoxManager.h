#ifndef SKYBOXMANAGER_H
#define SKYBOXMANAGER_H

#include <vector>

class SkyBox;

class SkyBoxManager
{
    public:
        SkyBoxManager();
        virtual ~SkyBoxManager();

    protected:

    private:
        std::vector<SkyBox*> skyboxes;
};

#endif // SKYBOXMANAGER_H
