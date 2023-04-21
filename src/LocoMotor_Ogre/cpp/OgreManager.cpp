//Ogre includes
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreGpuProgramManager.h>
#include <OgreShaderGenerator.h>
//SDL includes
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
//Std include
#include <iostream>
//OgreWrapper includes
#include "RenderScene.h"
#include "SGTechniqueResolverListener.h"
#include "OgreManager.h"



OgreWrapper::OgreManager* Singleton<OgreWrapper::OgreManager>::_instance = nullptr;

OgreWrapper::OgreManager::OgreManager(std::string name) {
	_root = nullptr;
	_activeScene = nullptr;
	_mShaderGenerator = nullptr;

	_root = new Ogre::Root();
	_root->showConfigDialog(nullptr);
	_root->initialise(false);
	InitWindow(name);
	LoadResources();
}

OgreWrapper::OgreManager::~OgreManager() {
	Shutdown();
}


OgreWrapper::RenderScene* OgreWrapper::OgreManager::CreateScene(std::string name) {
	if (_scenes.count(name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return _scenes[name];
	}

	OgreWrapper::RenderScene* sc;
	Ogre::SceneManager* sM = _root->createSceneManager();
	sc = new OgreWrapper::RenderScene(sM);
	_scenes.insert({ name, sc });
	if (_activeScene == nullptr) _activeScene = sc;
	_mShaderGenerator->addSceneManager(sc->GetMan());
	return sc;

}

OgreWrapper::RenderScene* OgreWrapper::OgreManager::GetScene(std::string name) {
	if (_scenes.count(name) == 0)
		return nullptr;

	return _scenes[name];
}

void OgreWrapper::OgreManager::Render() {
	if (_activeScene == nullptr) return;
	_activeScene->Render();
	_root->renderOneFrame();

}

Ogre::RenderWindow* OgreWrapper::OgreManager::GetRenderWindow() {
	return _mWindow.render;
}

void OgreWrapper::OgreManager::SetActiveScene(OgreWrapper::RenderScene* s) {
	_activeScene = s;
}

void OgreWrapper::OgreManager::LoadResources() {
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::String sec_name, type_name, arch_name;
	Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection();

	for (Ogre::ConfigFile::SettingsBySection_::const_iterator it = seci.cbegin(); it != seci.cend(); ++it) {
		sec_name = it->first;
		Ogre::ConfigFile::SettingsMultiMap settings = it->second;
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings.begin(); i != settings.end(); ++i) {
			type_name = i->first;
			arch_name = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				arch_name, type_name, sec_name);
		}
	}

	sec_name = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec_name);

	arch_name = genLocs.front().archive->getName();
	type_name = genLocs.front().archive->getType();

	std::string mRTShaderLibPath = arch_name + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type_name, sec_name);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type_name, sec_name);
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		if (mRTShaderLibPath.empty())
			return;

		// Create and register the material manager listener if it doesn't exist yet.
		if (!_mMaterialMgrListener) {
			_mMaterialMgrListener = new OgreWrapper::SGTechniqueResolverListener(_mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(_mMaterialMgrListener);
		}
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

OgreWrapper::NativeWindowPair OgreWrapper::OgreManager::InitWindow(std::string name) {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = _root->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt"))
			std::cout << "Gamecontroller Mappings Loaded" << "\n";
		else
			std::cout << "Gamecontroller Mappings NOT Loaded" << "\n";

		SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	}

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;

	_mWindow.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_mWindow.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_mWindow.render = _root->createRenderWindow(name, w, h, false, &miscParams);
	return _mWindow;
}


void OgreWrapper::OgreManager::Shutdown() {
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (_mMaterialMgrListener != nullptr) {
		Ogre::MaterialManager::getSingleton().removeListener(_mMaterialMgrListener);
		delete _mMaterialMgrListener;
		_mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (_mShaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy();
		_mShaderGenerator = nullptr;
	}

	for (auto it = _scenes.begin(); it != _scenes.end(); it = _scenes.erase(it)) {
		if (it->second = _activeScene) {
			_activeScene = nullptr;
		}
		_root->destroySceneManager(it->second->GetMan());
		delete it->second;
	}

	if (_mWindow.render != nullptr) {
		_root->destroyRenderTarget(_mWindow.render);
		_mWindow.render = nullptr;
	}

	if (_mWindow.native != nullptr) {
		SDL_DestroyWindow(_mWindow.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_mWindow.native = nullptr;
	}



	delete _root;
	_root = nullptr;
}


