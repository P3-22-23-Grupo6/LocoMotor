#include <OgreManager.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreGpuProgramManager.h>

#include <OgreShaderGenerator.h>
#include <OgreSGTechniqueResolverListener.h>
#include "RenderScene.h"
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include <iostream>


OgreWrapper::OgreManager* OgreWrapper::OgreManager::_instance = nullptr;

OgreWrapper::OgreManager::OgreManager () {
	_root = nullptr;

}

OgreWrapper::OgreManager::~OgreManager () {
}

OgreWrapper::OgreManager* OgreWrapper::OgreManager::GetInstance () {
	if (_instance != nullptr) return _instance;
	std::cerr << "Debes inicializar con OgreManager::init() antes de llamar a OgreManager::getInstance()!!\n";
	return nullptr;
}

bool OgreWrapper::OgreManager::Init (const char* name) {
	if (_instance == nullptr) _instance = new OgreWrapper::OgreManager ();
	_instance->_root = new Ogre::Root ();
	_instance->_root->showConfigDialog (nullptr);
	_instance->_root->initialise (false);
	_instance->InitWindow (name);
	_instance->loadResources ();
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
	try {
		_activeScene->Render ();
		_root->renderOneFrame ();
	}
	catch (Ogre::FileNotFoundException& e) {
		std::cout << e.getFullDescription () << "\n";
	}
}

Ogre::RenderWindow* OgreWrapper::OgreManager::GetRenderWindow () {
	return mWindow.render;
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

	arch_name = genLocs.front ().archive->getName ();
	type_name = genLocs.front ().archive->getType ();

	std::string mRTShaderLibPath = arch_name + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (mRTShaderLibPath + "/materials", type_name, sec_name);

	Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (mRTShaderLibPath + "/GLSL", type_name, sec_name);
	/*if (Ogre::GpuProgramManager::getSingleton ().isSyntaxSupported ("glsles")) {
		Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (mRTShaderLibPath + "/GLSL", type_name, sec_name);
		Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (mRTShaderLibPath + "/GLSLES", type_name, sec_name);
	}
	else if (Ogre::GpuProgramManager::getSingleton ().isSyntaxSupported ("glsl")) {

	}
	else if (Ogre::GpuProgramManager::getSingleton ().isSyntaxSupported ("hlsl")) {
		Ogre::ResourceGroupManager::getSingleton ().addResourceLocation (mRTShaderLibPath + "/HLSL", type_name, sec_name);
	}*/

	Ogre::MaterialManager::getSingleton ().setActiveScheme (Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	if (Ogre::RTShader::ShaderGenerator::initialize ()) {
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr ();
		// Core shader libs not found -> shader generating will fail.
		/*if (mRTShaderLibPath.empty ())
			return;*/


		// Create and register the material manager listener if it doesn't exist yet.
		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener (mShaderGenerator);
			Ogre::MaterialManager::getSingleton ().addListener (mMaterialMgrListener);
		}
	}

	Ogre::ResourceGroupManager::getSingleton ().initialiseAllResourceGroups ();
}

OgreWrapper::NativeWindowPair OgreWrapper::OgreManager::InitWindow (const char* name) {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = _root->getRenderSystem ()->getConfigOptions ();

	std::istringstream mode (ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit (SDL_INIT_VIDEO)) SDL_InitSubSystem (SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;
	//else  flags = SDL_WINDOW_RESIZABLE;

	mWindow.native = SDL_CreateWindow (name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION (&wmInfo.version);
	SDL_GetWindowWMInfo (mWindow.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString (size_t (wmInfo.info.win.window));

	mWindow.render = _root->createRenderWindow (name, w, h, false, &miscParams);
	return mWindow;
}


void OgreWrapper::OgreManager::Shutdown () {	
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton ().setActiveScheme (Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (mMaterialMgrListener != nullptr) {
		Ogre::MaterialManager::getSingleton ().removeListener (mMaterialMgrListener);
		delete mMaterialMgrListener;
		mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (mShaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy ();
		mShaderGenerator = nullptr;
	}

	if (mWindow.render != nullptr) {
		mWindow.render->removeAllViewports ();
		_root->destroyRenderTarget (mWindow.render);
		
		mWindow.render = nullptr;
	}

	if (mWindow.native != nullptr) {
		SDL_DestroyWindow (mWindow.native);
		SDL_QuitSubSystem (SDL_INIT_VIDEO);
		mWindow.native = nullptr;
	}

	for (auto it = _scenes.begin (); it != _scenes.end (); it = _scenes.erase (it)) {
		if (it->second = _activeScene) {
			_activeScene = nullptr;
		}
		_root->destroySceneManager (it->second->GetMan ());
		delete it->second;
	}


	delete _root;
	_root = nullptr;

	delete OgreManager::_instance;
	OgreManager::_instance = nullptr;
}
