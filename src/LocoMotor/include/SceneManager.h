#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Scene.h"
#include "Singleton.h"
#include <map>
#include <vector>
#include <string>
typedef uint32_t Uint32;

namespace LocoMotor {
	class ComponentsFactory;
	class Component;
	class MOTOR_API SceneManager : public Singleton<SceneManager> {
		friend Singleton<SceneManager>;

	public:

		/// @brief Create a new scene.
		/// @param name A string parameter that represents the name of the scene that is being
		/// created.
		/// @return a pointer to a newly created Scene object if the scene with the given name does not already
		/// exist in the _sceneInfo map.If the scene already exists, the function returns a nullptr.
		Scene* CreateScene(std::string name);

		/// @brief Change the active scene.
		/// @param name A string representing the name of the scene to be changed to.
		/// @return a pointer to the Scene object that was changed to, or nullptr if the
		/// scene with the given name does not exist.
		Scene* ChangeScene(std::string name);

		/// @brief Start a scene.
		/// @param scn A pointer to an object of type Scene, which is the scene that needs to be started.
		void StartScene(Scene* scn);

		/// @brief Get a scene by name.
		/// @param name a string representing the name of the scene to be retrieved from the SceneManager's map
		/// of scene information.
		/// @return a pointer to a `Scene` object. If the scene with the given name exists
		/// in the `_sceneInfo` map, a pointer to that scene is returned.Otherwise, a null
		/// pointer is returned.
		Scene* GetSceneByName(std::string name);

		/// @brief Get the currently active scene.
		/// @return  a pointer to the currently active scene in the `LocoMotor` game engine's `SceneManager`.
		Scene* GetCurrentScene();

		/// @brief Adds an returns an object to the current Scene on runtime
		/// @return  a pointer to the object created
		/// @param name of object
		GameObject* AddObjectRuntime(std::string objectName);

		/// @brief updates and renders the active scene in the LocoMotor game engine's SceneManager class.
		void Update();
		/// @brief Get the delta time.
		/// @return  the value of the private member variable `_deltaTime`,which is of type `float`.
		float GetDelta();

	private:
		SceneManager();
		~SceneManager();
		std::map<std::string, Scene*> _sceneInfo;
		Scene* _activeScene;
		Uint32 _lastTime;
		Uint32 _actTime;
		float _deltaTime;

	};
}