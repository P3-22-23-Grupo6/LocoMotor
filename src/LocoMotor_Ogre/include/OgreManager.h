#ifndef _OGRE_MANAGER_H
#define _OGRE_MANAGER_H

#include <map>

namespace Ogre {
	class Root;
	class RenderWindow;
}


namespace OgreWrapper {
	class RenderScene;
	class OgreManager {

	public:
		/// <summary>
		/// A method to get the <c>OgreManager</c> singleton instance.
		/// <c>OgreManager::init</c> must be called before any calls to <c>OgreManager::getInstance</c> or
		/// else it will return nullptr.
		/// </summary>
		/// <returns>The <c>OgreManager</c> singleton instance if init has been called beforehand. Returns <c>nullptr</c> if not</returns>
		static OgreWrapper::OgreManager* GetInstance ();

		/// <summary>
		/// Initializes the <c>OgreManager</c> singleton instance.
		/// This method must be called before any calls to <c>OgreManager::getInstance</c>.
		/// </summary>
		/// <param name="appName"> The name that will appear as the Window title </param>
		/// <returns><value>true</value> if the Instance was initialized correctly, <value>false</value> otherwise</returns>
		static bool Init (const char* appName);

		/// <summary>
		/// Creates a scene.
		/// If you try to create a scene with an already used name, the method will return that scene instead.
		/// </summary>
		/// <param name="name">Name for the new scene.</param>
		/// <returns>The newly created scene.<para/>
		/// If the name is already taken, the scene with that name will be returned instead.</returns>
		OgreWrapper::RenderScene* CreateScene (const char* name);

		/// <summary>
		/// Returns a created scene, searched by name in the list of scenes
		/// </summary>
		/// <param name="name"></param>
		/// <returns>A pointer to the scene with the indicated name<para/>
		/// If the name doesn't exist, getScene returns nullptr.</returns>
		OgreWrapper::RenderScene* GetScene (const char* name);

		/// @brief Renders a frame for the active render scene.
		void Render ();

	protected:
		static OgreManager* _instance;

		Ogre::Root* _root;
		Ogre::RenderWindow* _window;

		std::map<const char*, OgreWrapper::RenderScene*> _scenes;

		OgreWrapper::RenderScene* _activeScene;

		OgreManager ();
		~OgreManager ();
	};
}
#endif

