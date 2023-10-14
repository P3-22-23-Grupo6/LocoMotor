#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <string>
#include <unordered_map>

namespace OgreWrapper {
	class Camera;
	class RenderScene;
	class Node;
}


namespace LocoMotor {
	class Camera;
	class GameObject;
	class MOTOR_API Scene {
	public:
		Scene(std::string name);
		~Scene();
		/// @brief Initializes components for all game objects in the scene and sets the scene as active.
		void Start();
		/// @brief Updates all game objects in the scene and sets the camera position based on the
		/// position of a specific game object.
		/// @param dt stands for delta time, which is the time elapsed since the last frame update. It is
		/// used to ensure that the game runs at a consistent speed regardless of the performance of the
		/// computer running it.
		void Update(float dt);
		/// @brief Renders the scene using OgreWrapper and _renderScn.
		void Render();
		/// @brief Deactivate the scene
		void DeActivate();
		/// @brief Returns the active status of a scene in C++.
		/// @return value of the private member variable `_isActiveScene`.
		bool GetActiveStatus();
		/// @brief  Returns the name of a scene as a string.
		/// @return scene name
		std::string GetSceneName();

		/// @brief Set the camera of a scene.
		/// @param cam A camera to set as the active camera of the scene.
		void SetSceneCam(OgreWrapper::Camera* cam);

		/// @brief Adds a new game object to the scene or returns an existing one with the same name.
		/// @param name A string representing the name of the GameObject to be added to the Scene.
		/// @return the pointer of the new GameObject.
		GameObject* AddGameobject(std::string name);
		/// @brief Adds a new game object *during gameplay* to the scene or returns an existing one with the same name.
		/// @param name A string representing the name of the GameObject to be added to the Scene.
		/// @return the pointer of the new GameObject.
		GameObject* AddGameobjectRuntime(std::string name);
		/// @brief Removes the selected GameObject from the list
		/// @param name The name of the Object to remove
		void RemoveGameobject(std::string name);
		/// @brief Returns a GameObject pointer by searching for its name in a Scene's list of GameObjects.
		/// @param name Is a string parameter that represents the name of the GameObject that is being
		/// searched for in the Scene's list of GameObjects.
		/// @return pointer to a GameObject. If the GameObject with the given name exists in the _gameObjList
		/// map, then a pointer to that GameObject is returned.Otherwise, a null pointer is returned.
		GameObject* GetObjectByName(std::string name);
		/// @brief Returns a pointer to the camera GameObject in the Scene.
		/// @return Pointer to a GameObject object, specifically the camera_gObj object.
		GameObject* GetCamera();

		/// @brief Sets the GameObject for the camera
		/// @param cam GameObject with the camera
		void SetCamObj(GameObject* cam);
		/// @brief Returns if the scene has to be destroyed
		/// @return _toDestroy 
		bool ToDestroy();
		/// @brief Destroys all the gameObjects on the scene
		void Destroy();

	private:

		Camera* _currentCam;

		OgreWrapper::Camera* _cam;

		std::string _name;

		bool _isActiveScene = false;

		OgreWrapper::RenderScene* _renderScn;

		std::unordered_map<std::string, GameObject*> _gameObjList;
		std::unordered_map<std::string, GameObject*> _gameObjBufferList;

		GameObject* _camera_gObj;

		bool _toDestroy = false;
	};
}