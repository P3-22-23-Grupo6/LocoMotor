#include "Scene.h"

Scene::Scene(std::string nombre) {
	_name = nombre;


}

Scene::~Scene() {}


void Scene:: Start() {
	_isActiveScene = true;

}

void Scene::Update() {
	//si no esta activa que no haga nada
	if (_isActiveScene) {}


}
void Scene::Render() {}

//?
void Scene::Deactivate() {
	_isActiveScene = false;

}


//Activate

bool Scene::GetActiveStatus() {
	return _isActiveScene;
}

std::string Scene::GetSceneName() {
	return _name;
}


/*void Scene::addObject(GameObject* obj){
    _gameObjList.push_back(obj);

}
*/
