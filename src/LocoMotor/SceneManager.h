#pragma once
#include "Scene.h"
#include "Singleton.h"
#include <map>
#include <vector>
#include <string>
typedef uint32_t Uint32;

//Unordered map de string(nombre de escena) y Scene(datos de esta)

namespace LocoMotor {
	class ComponentsFactory;
	class Component;
	class SceneManager : public Singleton<SceneManager> {
		friend Singleton<SceneManager>;

	public:
		
		//Crear escenas

		Scene* CreateScene(std::string nombre);


		//Cambiar entre escenas

		Scene* ChangeScene(std::string name);


		void StartScene(Scene* scn);


		Scene* GetSceneByName(std::string name);
		 
		Scene* GetCurrentScene();

		

		void Update();
		float GetDelta() {
			return _actTime;
		};

	private:
		SceneManager();
		~SceneManager();
		std::map<std::string, Scene*> _sceneInfo;

		//std::string _currScn;
		Scene* _activeScene;

		Uint32 _lastTime;
		Uint32 _actTime;
		float _deltaTime;

	};
}