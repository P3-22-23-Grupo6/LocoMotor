#ifndef _OGRE_MANAGER_H
#define _OGRE_MANAGER_H

#include <map>
#include <OgreMaterialManager.h>

#include "Singleton.h"
namespace Ogre {
	class Root;
	class RenderWindow;
	class OverlaySystem;
	namespace RTShader {
		class ShaderGenerator;
	}
}

struct SDL_Window;
namespace OgreWrapper {
	class RenderScene;

	struct NativeWindowPair {
		Ogre::RenderWindow* render = nullptr;
		SDL_Window* native = nullptr;
	};
	class OgreManager : public LocoMotor::Singleton<OgreManager> {
		friend LocoMotor::Singleton<OgreManager>;
	public:
		/// @brief Creates a scene, if you try to create a scene with an already used name, the method will return that scene instead.
		/// @param name Name for the new scene.
		/// @return The newly created scene.
		///	If the name is already taken, the scene with that name will be returned instead.
		OgreWrapper::RenderScene* CreateScene(std::string name);

		/// @brief Returns a created scene, searched by name in the list of scenes
		/// @param name Name of the scene.
		/// @return A pointer to the scene with the indicated name
		/// If the name doesn't exist, getScene returns nullptr.
		OgreWrapper::RenderScene* GetScene(std::string name);


		/// @brief Renders a frame.

		void Render();

		/// @brief 
		/// Returns RenderWindow
		/// @return Render window of Ogre
		Ogre::RenderWindow* GetRenderWindow();

		/// @brief
		/// Sets the active scene for the manager

		/// @param s The scene to become active
		void SetActiveScene(OgreWrapper::RenderScene* s);
		/// @brief Returns the render window height
		int GetWindowHeight();
		/// @brief Returns the render window width
		int GetWindowWidth();
	protected:
		Ogre::Root* _root;
		NativeWindowPair _mWindow;

		std::map<std::string, OgreWrapper::RenderScene*> _scenes;

		Ogre::MaterialManager::Listener* _mMaterialMgrListener = nullptr;

		OgreWrapper::RenderScene* _activeScene;

		Ogre::RTShader::ShaderGenerator* _mShaderGenerator;

		Ogre::OverlaySystem* _ovrSys;

		/// @brief Creates a new OgreManager.

		/// @param name The name for the window
		OgreManager(std::string name);
		~OgreManager();

		/// @brief Loads the resouces and initializes the RTShaderSytem
		void LoadResources();

		/// @brief Initializes the window
		/// @param name The Window title
		/// @return
		NativeWindowPair InitWindow(std::string name);

		/// @brief
		/// Shuts down Ogre and releases all the memory related to it

		void Shutdown();

	};
}
#endif

