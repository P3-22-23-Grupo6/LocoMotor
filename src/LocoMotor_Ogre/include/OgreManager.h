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

class SDL_Window;
namespace OgreWrapper{
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
		OgreWrapper::RenderScene* CreateScene (std::string name);

		/// <summary>
		/// Returns a created scene, searched by name in the list of scenes
		/// </summary>
		/// <param name="name"></param>
		/// <returns>A pointer to the scene with the indicated name<para/>
		/// If the name doesn't exist, getScene returns nullptr.</returns>
		OgreWrapper::RenderScene* GetScene (std::string name);

		/// <summary>
		/// Renderiza un frame.
		///</summary> 
		void Render ();

		/// @brief 
		/// Devuelve la RenderWindow
		/// @return Ventana de renderizado de Ogre
		Ogre::RenderWindow* GetRenderWindow ();

		void SetActiveScene (OgreWrapper::RenderScene* s) {
			_activeScene = s;
		}

		void loadResources ();

		Ogre::RTShader::ShaderGenerator* mShaderGenerator;

		NativeWindowPair InitWindow (std::string name);

		void Shutdown ();

	protected:
		Ogre::Root* _root;
		NativeWindowPair mWindow;

		std::map<std::string, OgreWrapper::RenderScene*> _scenes;

		Ogre::MaterialManager::Listener* mMaterialMgrListener = nullptr;

		OgreWrapper::RenderScene* _activeScene;

		OgreManager (std::string name);
		~OgreManager ();
	};
}
#endif

