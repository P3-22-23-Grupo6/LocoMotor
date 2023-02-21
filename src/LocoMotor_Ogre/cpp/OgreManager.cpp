#include <OgreManager.h>
#include <iostream>

OgreWrapper::OgreManager* OgreWrapper::OgreManager::instance = nullptr;

OgreWrapper::OgreManager::OgreManager() {
	mRoot = nullptr;
	mWindow = nullptr;
}

OgreWrapper::OgreManager::~OgreManager() {
	delete mWindow;
	delete mRoot;
}

OgreWrapper::OgreManager* OgreWrapper::OgreManager::getInstance() {
	if (instance != nullptr) return instance;
	std::cerr << "Debes inicializar con OgreManager::init() antes de llamar a OgreManager::getInstance()!!\n";
	return nullptr;
}

bool OgreWrapper::OgreManager::init(const char* name) {
	if (instance == nullptr) instance = new OgreWrapper::OgreManager();
	instance->mRoot = new Ogre::Root();
	instance->mRoot->showConfigDialog(nullptr);
	instance->mWindow = instance->mRoot->initialise(true, name);
	return instance->mRoot->isInitialised();
}

OgreWrapper::Scene* OgreWrapper::OgreManager::createScene(const char* name) {
	if (scenes.count(name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return scenes[name];
	}

	OgreWrapper::Scene* sc;
	sc = new OgreWrapper::Scene(mRoot->createSceneManager());
	scenes.insert({ name, sc });
	return sc;

}

OgreWrapper::Scene* OgreWrapper::OgreManager::getScene(const char* name)
{
	if(scenes.count(name) == 0) 
		return nullptr;

	return scenes[name];
}
