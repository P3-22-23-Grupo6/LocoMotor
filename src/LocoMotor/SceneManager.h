#pragma once
#include "Scene.h"
#include <map>
#include <string>

//Unordered map de string(nombre de escena) y Scene(datos de esta)

namespace LocoMotor {
	class SceneManager {


	public:
		SceneManager();
		~SceneManager();
		//Crear escenas

		Scene* CreateScene(std::string nombre);


		//Cambiar entre escenas

		Scene* ChangeScene(std::string name);


		void StartScene(Scene* scn);


		Scene* GetSceneByName(std::string name);

		void Update();

	private:
		std::map<std::string, Scene*> _sceneInfo;

		//std::string _currScn;
		Scene* _activeScene;

		float _lastTime;
		float _actTime;
		float _deltaTime;

	};
}