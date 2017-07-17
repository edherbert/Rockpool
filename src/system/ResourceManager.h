#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../map/Main.h"

class Main;

struct resourceLocation{
    wxString path;
    std::vector<wxString>resources;
};

class ResourceManager
{
    public:
        ResourceManager(Main *main);
        virtual ~ResourceManager();

        void checkResourceLocations();

        std::vector<resourceLocation*> getResources();

    protected:

    private:
        Main *main;

        std::vector<resourceLocation*>locations;
};

#endif // RESOURCEMANAGER_H
