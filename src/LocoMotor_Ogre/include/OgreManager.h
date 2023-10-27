#ifndef _OGRE_MANAGER_H
#define _OGRE_MANAGER_H

#include <map>
#include <OgreMaterialManager.h>
#include "Camera.h"
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
	class Camera;
	struct NativeWindowPair {
		Ogre::RenderWindow* render = nullptr;
		SDL_Window* native = nullptr;
	};
	class OgreManager : public LocoMotor::Singleton<OgreManager> {
		friend LocoMotor::Singleton<OgreManager>;
	public:
		Ogre::TexturePtr tex;
		/// @brief Initializes the OgreManager singleton with a name for the new window
		/// @param name Name for the window.
		/// @return whether the initialize went well or not.
		///	If the name is already taken, the scene with that name will be returned instead.
		std::string Initialize(std::string name);


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

		//Material Manipulation
		void ChangeTexOffset(std::string materialName, float newX, float newY);
		void RenderToImage();
		void UpdateRenderTextures();
		void CreateBillboard(Ogre::Vector3 billPos, std::string billMat);
		/// @brief Adds one everytime a camera is Created(for different viewports)
		/// @brief Es bastante enrevesado pero nadie va a tocarlo y funciona. en caso de tocamiento tejodes.png
		/// @params shouldAdd if true, adds +1 to index(if creating camera; only calling from camera)
		int GetLastCamIndex(bool shouldAdd = false);
	protected:
		int lastCamIndex;
		Ogre::Root* _root;
		Ogre::SceneManager* sM;
		NativeWindowPair _mWindow;

		std::map<std::string, OgreWrapper::RenderScene*> _scenes;

		Ogre::MaterialManager::Listener* _mMaterialMgrListener = nullptr;

		OgreWrapper::RenderScene* _activeScene;

		Ogre::RTShader::ShaderGenerator* _mShaderGenerator;

		Ogre::OverlaySystem* _ovrSys;

		/// @brief Creates a new OgreManager.
		/// @param name The name for the window
		OgreManager();
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
		std::list<Ogre::RenderTexture*> renderTexList;
	};
}
#endif

