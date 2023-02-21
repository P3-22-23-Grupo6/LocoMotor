#ifndef _OGRE_MANAGER_H
#define _OGRE_MANAGER_H


#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <map>


#include "Scene.h"

namespace OgreWrapper
{
	class OgreManager
	{
	protected:
		static OgreManager* instance;

		Ogre::Root* mRoot;
		Ogre::RenderWindow* mWindow;

		std::map<const char*, Scene*> scenes;

		OgreManager();
		~OgreManager();
	public:
		/// <summary>
		/// A method to get the <c>OgreManager</c> singleton instance.
		/// <c>OgreManager::init</c> must be called before any calls to <c>OgreManager::getInstance</c> or
		/// else it will return nullptr.
		/// </summary>
		/// <returns>The <c>OgreManager</c> singleton instance if init has been called beforehand. Returns <c>nullptr</c> if not</returns>
		static OgreManager* getInstance();

		/// <summary>
		/// Initializes the <c>OgreManager</c> singleton instance.
		/// This method must be called before any calls to <c>OgreManager::getInstance</c>.
		/// </summary>
		/// <param name="appName"> The name that will appear as the Window title </param>
		/// <returns><value>true</value> if the Instance was initialized correctly, <value>false</value> otherwise</returns>
		static bool init(const char* appName);

		/// <summary>
		/// Creates a scene.
		/// If you try to create a scene with an already used name, the method will return that scene instead.
		/// </summary>
		/// <param name="name">Name for the new scene.</param>
		/// <returns>The newly created scene.<para/>
		/// If the name is already taken, the scene with that name will be returned instead.</returns>
		OgreWrapper::Scene* createScene(const char* name);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <returns>A pointer to the scene with the indicated name<para/>
		/// If the name doesn't exist, getScene returns nullptr.</returns>
		OgreWrapper::Scene* getScene(const char* name);
		void render() { mRoot->startRendering(); };
	};
}
#endif

