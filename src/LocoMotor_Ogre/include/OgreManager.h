#ifndef _OGRE_MANAGER_H
#define _OGRE_MANAGER_H

#include <map>
#include <OgreMaterialManager.h>

#include "Singleton.h"
namespace Ogre {
	class Root;
	class RenderWindow;
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
	class OgreManager : public Singleton<OgreManager> {
		friend Singleton<OgreManager>;
	public:
		/// <summary>
		/// Creates a scene.
		/// If you try to create a scene with an already used name, the method will return that scene instead.
		/// </summary>
		/// <param name="name">Name for the new scene.</param>
		/// <returns>The newly created scene.<para/>
		/// If the name is already taken, the scene with that name will be returned instead.</returns>
		OgreWrapper::RenderScene* CreateScene(std::string name);

		/// <summary>
		/// Returns a created scene, searched by name in the list of scenes
		/// </summary>
		/// <param name="name"></param>
		/// <returns>A pointer to the scene with the indicated name<para/>
		/// If the name doesn't exist, getScene returns nullptr.</returns>
		OgreWrapper::RenderScene* GetScene(std::string name);

		/// <summary>
		/// Renderiza un frame.
		///</summary> 
		void Render();

		/// @brief 
		/// Devuelve la RenderWindow
		/// @return Ventana de renderizado de Ogre
		Ogre::RenderWindow* GetRenderWindow();

		/// <summary>
		/// Sets the active scene for the manager
		/// </summary>
		/// <param name="s">The scene to become active</param>
		void SetActiveScene(OgreWrapper::RenderScene* s);
	protected:
		Ogre::Root* _root;
		NativeWindowPair _mWindow;

		std::map<std::string, OgreWrapper::RenderScene*> _scenes;

		Ogre::MaterialManager::Listener* _mMaterialMgrListener = nullptr;

		OgreWrapper::RenderScene* _activeScene;

		Ogre::RTShader::ShaderGenerator* _mShaderGenerator;

		/// <summary>
		/// Creates a new OgreManager.
		/// </summary>
		/// <param name="name">The name for the window</param>
		OgreManager(std::string name);
		~OgreManager();

		/// <summary>
		/// Loads the resouces and initializes the RTShaderSytem
		/// </summary>
		void LoadResources();

		/// <summary>
		/// Initializes the window
		/// </summary>
		/// <param name="name">The Window title</param>
		/// <returns></returns>
		NativeWindowPair InitWindow(std::string name);

		/// <summary>
		/// Shuts down Ogre and releases all the memory related to it
		/// </summary>
		void Shutdown();

	};
}
#endif

