#include "SceneManager.h"
#include <SDL.h>

#include "ComponentsFactory.h"

using namespace LocoMotor;

SceneManager* Singleton<SceneManager>::_instance = nullptr;

SceneManager::SceneManager() {
	_activeScene = nullptr;
	_actTime = 0;
	_lastTime = 0;
	_deltaTime = 0.1f;
	factory = new ComponentsFactory();
}

SceneManager::~SceneManager() {
	std::map<std::string, Scene*>::const_iterator it;
	for (it = _sceneInfo.cbegin(); it != _sceneInfo.cend(); it = _sceneInfo.erase(it)) {
		delete it->second;
	}
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
		//si hay alguna escena activa, se desactiva
		if (_activeScene != nullptr) {

			_activeScene->Deactivate();
		}

		StartScene(it->second);
		_activeScene = it->second;
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

Scene* LocoMotor::SceneManager::GetCurrentScene()
{
	return _activeScene;
}

Component* LocoMotor::SceneManager::CreateComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params)
{
	return factory->CreateComponent(name, params);
}

void LocoMotor::SceneManager::Update() {

	_actTime = SDL_GetTicks();
	_deltaTime = _actTime - (float)_lastTime;
	_lastTime = _actTime;

	if (_deltaTime <= 0) _deltaTime = 0.001f;

	if (_activeScene != nullptr) {
		_activeScene->Update(_deltaTime);
		_activeScene->Render();
	}

}

void SceneManager::StartScene(Scene* scn) {
	scn->Start();
}