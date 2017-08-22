#include "OgreComponent.h"

OgreComponent::OgreComponent(){
    Ogre::String resourcesString = "../setup/resources.cfg";
    Ogre::String pluginsString = "../setup/plugins.cfg";

    root = new Ogre::Root(pluginsString);

    Ogre::ConfigFile cf;
    cf.load(resourcesString);

    Ogre::String name, locType;
    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

    while (secIt.hasMoreElements()){
        Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;

        for (it = settings->begin(); it != settings->end(); ++it){
          locType = it->first;
          name = it->second;

          Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }

    if (!(root->restoreConfig() || root->showConfigDialog())){
        std::cout << "Could not restore configuration file, closing window." << std::endl;
    }
    //root->showConfigDialog();

    root->initialise(false);

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

OgreComponent::~OgreComponent(){

}

void OgreComponent::setupPlane(){
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane(
        "Rockpool_DefaultPlane",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1, 1, 1, 1,
        true,
        1, 1, 1,
        Ogre::Vector3::UNIT_Z);
}
