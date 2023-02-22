#include <OgreManager.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include "RenderScene.h"
#include <iostream>


OgreWrapper::OgreManager* OgreWrapper::OgreManager::_instance = nullptr;

OgreWrapper::OgreManager::OgreManager () {
	_root = nullptr;
	_window = nullptr;
}

OgreWrapper::OgreManager::~OgreManager () {
	delete _window;
	delete _root;
}

OgreWrapper::OgreManager* OgreWrapper::OgreManager::GetInstance () {
	if (_instance != nullptr) return _instance;
	std::cerr << "Debes inicializar con OgreManager::init() antes de llamar a OgreManager::getInstance()!!\n";
	return nullptr;
}

bool OgreWrapper::OgreManager::Init (const char* name) {
	if (_instance == nullptr) _instance = new OgreWrapper::OgreManager ();
	_instance->_root = new Ogre::Root ();
	_instance->loadResources ();
	_instance->_root->showConfigDialog (nullptr);
	_instance->_window = _instance->_root->initialise (true, name);
	return _instance->_root->isInitialised ();
}

OgreWrapper::RenderScene* OgreWrapper::OgreManager::CreateScene (const char* name) {
	if (_scenes.count (name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return _scenes[name];
	}

	OgreWrapper::RenderScene* sc;
	sc = new OgreWrapper::RenderScene (_root->createSceneManager ());
	_scenes.insert ({ name, sc });
	return sc;

}

OgreWrapper::RenderScene* OgreWrapper::OgreManager::GetScene (const char* name) {
	if (_scenes.count (name) == 0)
		return nullptr;

	return _scenes[name];
}

void OgreWrapper::OgreManager::Render () {
	_activeScene->Render ();
	_root->renderOneFrame ();
}

Ogre::RenderWindow* OgreWrapper::OgreManager::GetRenderWindow () {
	return _window;
}

void OgreWrapper::OgreManager::loadResources () {
	Ogre::ConfigFile cf;
	cf.load ("resources.cfg");

	Ogre::String sec_name, type_name, arch_name;
	Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection ();

	for (Ogre::ConfigFile::SettingsBySection_::const_iterator it = seci.cbegin (); it != seci.cend (); ++it) {
		sec_name = it->first;
		Ogre::ConfigFile::SettingsMultiMap settings = it->second;
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings.begin (); i != settings.end (); ++i) {
			type_name = i->first;
			arch_name = i->second;
			Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (
				arch_name, type_name, sec_name);
		}
	}

	sec_name = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton ().getResourceLocationList (sec_name);

	Ogre::ResourceGroupManager::getSingleton ().initialiseAllResourceGroups ();
}