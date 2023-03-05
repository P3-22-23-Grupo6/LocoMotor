#include "SceneManager.h"


SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {

}

Scene* SceneManager::CreateScene(std::string nombre) {
	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(nombre);
	if (it == _sceneInfo.end()) {

		Scene* newScene = new Scene(nombre);


		_sceneInfo.insert({ nombre, newScene });

		return newScene;
	}

	else {


		//si devuelve nullptr mandar mensaje al logSystem
		return nullptr;
	}

}

Scene* SceneManager::ChangeScene(std::string name) {
	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(name);

	if (it != _sceneInfo.end()) {

		std::map<std::string, Scene*>::iterator itAct = _sceneInfo.begin();
		while (itAct != _sceneInfo.end() && itAct->second->GetActiveStatus()) {
			itAct++;
		}

		//si hay alguna escena activa, se desactiva
		if (itAct != _sceneInfo.end()) {

			itAct->second->Deactivate();
		}


		StartScene(it->second);

		return it->second;
		//return "Cambiada la escena";


	}
	else {
		//Mensaje a logsystem
		return nullptr;
		//return "No existe la escena" + name;
	}

}

Scene* SceneManager::GetSceneByName(std::string name) {

	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(name);
	if (it != _sceneInfo.end()) {

		return it->second;
	}
	else {
		return nullptr;
	}

}

void SceneManager::StartScene(Scene* scn) {
	scn->Start();
}