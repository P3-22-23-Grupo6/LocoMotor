#include <OgreManager.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include "RenderScene.h"
#include <iostream>


OgreWrapper::OgreManager* OgreWrapper::OgreManager::_instance = nullptr;

OgreWrapper::OgreManager::OgreManager() {
	_root = nullptr;
	_window = nullptr;
}

OgreWrapper::OgreManager::~OgreManager() {
	delete _window;
	delete _root;
}

OgreWrapper::OgreManager* OgreWrapper::OgreManager::GetInstance() {
	if (_instance != nullptr) return _instance;
	std::cerr << "Debes inicializar con OgreManager::init() antes de llamar a OgreManager::getInstance()!!\n";
	return nullptr;
}

bool OgreWrapper::OgreManager::Init(const char* name) {
	if (_instance == nullptr) _instance = new OgreWrapper::OgreManager();
	_instance->_root = new Ogre::Root();
	_instance->_root->showConfigDialog(nullptr);
	_instance->_window = _instance->_root->initialise(true, name);
	return _instance->_root->isInitialised();
}

OgreWrapper::RenderScene* OgreWrapper::OgreManager::CreateScene(const char* name) {
	if (_scenes.count(name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return _scenes[name];
	}

	OgreWrapper::RenderScene* sc;
	sc = new OgreWrapper::RenderScene(_root->createSceneManager());
	_scenes.insert({ name, sc });
	return sc;

}

OgreWrapper::RenderScene* OgreWrapper::OgreManager::GetScene(const char* name) {
	if (_scenes.count(name) == 0)
		return nullptr;

	return _scenes[name];
}

void OgreWrapper::OgreManager::Render() {
	_activeScene->Render();
	_root->renderOneFrame();
}

Ogre::RenderWindow* OgreWrapper::OgreManager::GetRenderWindow()
{
	return _window;
}

