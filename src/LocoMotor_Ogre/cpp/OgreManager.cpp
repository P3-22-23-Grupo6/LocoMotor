#include <OgreManager.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreGpuProgramManager.h>
#include <OgreMaterialManager.h>
#include <OgreShaderGenerator.h>
#include <OgreSGTechniqueResolverListener.h>
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
	_instance->_root->showConfigDialog (nullptr);
	_instance->_window = _instance->_root->initialise (true, name);
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

		Ogre::MaterialManager::Listener* mMaterialMgrListener = nullptr;
		// Create and register the material manager listener if it doesn't exist yet.
		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener (mShaderGenerator);
			Ogre::MaterialManager::getSingleton ().addListener (mMaterialMgrListener);
		}
	}

	Ogre::ResourceGroupManager::getSingleton ().initialiseAllResourceGroups ();
}