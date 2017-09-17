#ifndef SKYBOXMANAGER_H
#define SKYBOXMANAGER_H

#include <vector>
#include <wx/string.h>

class SkyBox;

static const wxString skyBoxImageNames[6] = {"Front", "Back", "Left", "Right", "Top", "Bottom"};

class SkyBoxManager
{
    public:
        SkyBoxManager();
        virtual ~SkyBoxManager();

        void addSkyBox(SkyBox *skybox);

        int getSkyBoxCount();
        SkyBox* getSkyBoxAt(int index);
        void deleteSkyBoxAt(int index);

    protected:

    private:
        std::vector<SkyBox*> skyboxes;
};

#endif // SKYBOXMANAGER_H
