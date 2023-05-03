#include "SceneManager.h"
#include <SDL.h>

#include "ComponentsFactory.h"
#include "OgreManager.h"

using namespace LocoMotor;

/* Initializing the static member variable `_instance` of the `Singleton` template class with a null
pointer value. This variable is used to store the single instance of the `SceneManager` class that
is created and accessed through the `GetInstance()` method of the `Singleton` template class. */
SceneManager* Singleton<SceneManager>::_instance = nullptr;

/**
 * This is the constructor for the SceneManager class, initializing its member variables.
 */
SceneManager::SceneManager() {
	_activeScene = nullptr;
	_actTime = 0;
	_lastTime = 0;
	_deltaTime = 0.1f;
}

/**
 * The destructor of the SceneManager class that deletes all scenes stored in a map.
 */
SceneManager::~SceneManager() {
	std::map<std::string, Scene*>::const_iterator it;
	for (it = _sceneInfo.cbegin(); it != _sceneInfo.cend(); it = _sceneInfo.erase(it)) {
		delete it->second;
	}
}

/**
 * This function creates a new scene and adds it to the scene map if it doesn't already exist.
 * @brief Create a new scene.
 * @param nombre A string parameter that represents the name of the scene that is being
 * created.
 * 
 * @return a pointer to a newly created Scene object if the scene with the given name does not already
 * exist in the _sceneInfo map. If the scene already exists, the function returns a nullptr.
 */
Scene* SceneManager::CreateScene(std::string nombre) {
	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(nombre);
	if (it == _sceneInfo.end()) {

		Scene* newScene = new Scene(nombre);


		_sceneInfo.insert({ nombre, newScene });

		if (_activeScene == nullptr) {
			_activeScene = newScene;
		
		}

		return newScene;
	}

	else {


		//si devuelve nullptr mandar mensaje al logSystem
		return nullptr;
	}

}

/**
 * This function changes the active scene in a SceneManager object to the scene with the specified
 * name.
 * @brief Change the active scene.
 * @param name a string representing the name of the scene to be changed to.
 * 
 * @return The method returns a pointer to the Scene object that was changed to, or nullptr if the
 * scene with the given name does not exist.
 */
Scene* SceneManager::ChangeScene(std::string name) {
	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(name);
	OgreWrapper::OgreManager* renderMan = OgreWrapper::OgreManager::GetInstance();

	if (it != _sceneInfo.end()) {
		//si hay alguna escena activa, se desactiva
		if (_activeScene != nullptr && _activeScene != it->second) {

			_activeScene->DeActivate();
		}


		StartScene(it->second);
		renderMan->SetActiveScene(renderMan->GetScene(it->second->GetSceneName()));
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


/**
 * This function returns a pointer to a Scene object with a given name, if it exists in a map of scene
 * information.
 * @brief Get a scene by name.
 * @param name a string representing the name of the scene to be retrieved from the SceneManager's map
 * of scene information.
 * 
 * @return The function `GetSceneByName` returns a pointer to a `Scene` object. If the scene with the
 * given name exists in the `_sceneInfo` map, a pointer to that scene is returned. Otherwise, a null
 * pointer is returned.
 */
Scene* SceneManager::GetSceneByName(std::string name) {

	std::map<std::string, Scene*>::iterator it = _sceneInfo.find(name);
	if (it != _sceneInfo.end()) {

		return it->second;
	}
	else {
		return nullptr;
	}

}

/**
 * The function returns the currently active scene in the LocoMotor's SceneManager.
 * @brief Get the currently active scene.
 * @return The `GetCurrentScene()` function is returning a pointer to the currently active scene in the
 * `LocoMotor` game engine's `SceneManager`.
 */
Scene* LocoMotor::SceneManager::GetCurrentScene()
{
	return _activeScene;
}

/**
 * This function updates and renders the active scene in the LocoMotor game engine's SceneManager
 * class.
 */
void LocoMotor::SceneManager::Update() {

	_actTime = SDL_GetTicks();
	_deltaTime = (float)_actTime - (float)_lastTime;
	_lastTime = _actTime;

	if (_deltaTime <= 0) _deltaTime = 0.001f;

	Scene* sc = _activeScene;
	if (_activeScene != nullptr) {
		sc->Update(_deltaTime); 
		sc->Render();
	}
	if (sc!=nullptr && sc->ToDestroy()) {
		sc->Destroy();
	}
}

/**
 * This function returns the delta time in the LocoMotor's SceneManager.
 * @brief Get the delta time.
 * @return The method `GetDelta()` is returning the value of the private member variable `_deltaTime`,
 * which is of type `float`.
 */
float LocoMotor::SceneManager::GetDelta() {
	return _deltaTime;
}

/**
 * This function starts a given scene by calling its Start() method.
 * @brief Start a scene.
 * @param scn A pointer to an object of type Scene, which is the scene that needs to be started.
 */
void SceneManager::StartScene(Scene* scn) {
	scn->Start();
}