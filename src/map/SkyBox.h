#ifndef SKYBOX_H
#define SKYBOX_H

#include <wx/string.h>

class SkyBox
{
    public:
        SkyBox();
        virtual ~SkyBox();

        void setSkyBoxValue(int index, const wxString& value);
        wxString getSkyBoxValue(int index);
        wxString getName();

        void copyValuesFrom(SkyBox *skybox);
        void setName(const wxString& name);

    protected:

    private:
        wxString name;
        wxString paths[6];
};

#endif // SKYBOX_H
