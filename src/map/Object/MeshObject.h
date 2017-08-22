#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "Object.h"
#include <wx/string.h>

class MeshObject : public Object
{
    public:
        MeshObject(Ogre::SceneManager *sceneManager, const wxString &name, const wxString &path);
        virtual ~MeshObject();

    protected:

    private:
        wxString name;
        wxString path;

        Ogre::Entity *objectEntity;
};

#endif // MESHOBJECT_H
