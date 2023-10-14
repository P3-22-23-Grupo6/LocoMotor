#include "Scene.h"
#include "Camera.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Renderer3D.h"
#include "RigidBody.h"
#include "PhysicsManager.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "GameObject.h"


using namespace LocoMotor;
Scene::Scene(std::string name) {
	_name = name;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);
}

Scene::~Scene() {
	std::unordered_map<std::string, GameObject*>::const_iterator it;
	for (it = _gameObjList.cbegin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}
	for (it = _gameObjBufferList.cbegin(); it != _gameObjBufferList.end(); it = _gameObjBufferList.erase(it)) {
		delete it->second;
	}
	_renderScn = nullptr;
	_cam = nullptr;
	
}


void Scene::Start() {
	_toDestroy = false;
	for (auto& obj : _gameObjList) {
		obj.second->StartComp();
	}
	_isActiveScene = true;
}


void Scene::Update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;
	}
	for (auto& obj : _gameObjList) {
		obj.second->Update(dt);
	}
	//End of loop, once all objects are Updated, add buffered objects
	for (auto& obj : _gameObjBufferList) {
		_gameObjList.insert(obj);
	}
	_gameObjBufferList.clear();
}

void Scene::Render() {
	_renderScn->Render();
	OgreWrapper::OgreManager::GetInstance()->Render();
}


void Scene::DeActivate() {
	_toDestroy = true;
}


bool LocoMotor::Scene::ToDestroy() {
	return _toDestroy;
}

void Scene::Destroy() {
	_isActiveScene = false;
	std::unordered_map<std::string, GameObject*>::iterator it;
	for (it = _gameObjList.begin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		_renderScn->DestroyNode(it->second->GetName());
		delete it->second;
	}
	_renderScn->Deactivate();
}


bool Scene::GetActiveStatus() {
	return _isActiveScene;
}


std::string Scene::GetSceneName() {
	return _name;
}


void Scene::SetSceneCam(OgreWrapper::Camera* camera) {
	_cam = camera;
	_renderScn->SetActiveCamera(_cam);
}


GameObject* LocoMotor::Scene::AddGameobject(std::string name) {
	if (_gameObjList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjList[name];	
	}
	GameObject* newObj = new GameObject(name);
	newObj->SetContext(this);
	_gameObjList.insert({ name, newObj });
	return newObj;
}
GameObject* LocoMotor::Scene::AddGameobjectRuntime(std::string name) {
	if (_gameObjList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjList[name];
	}
	if (_gameObjBufferList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjBufferList[name];
	}
	GameObject* newObj = new GameObject(name);
	newObj->SetContext(this);
	_gameObjBufferList.insert({ name, newObj });
	return newObj;
}

void LocoMotor::Scene::RemoveGameobject(std::string name) {
	if (_gameObjList.count(name) == 0) {
	#ifdef DEBUG
		std::cerr << "No existe un objeto con el nombre " << name << std::endl;
	#endif // DEBUG
		return;
	}
	delete _gameObjList[name];
	_gameObjList.erase(name);
	_renderScn->DestroyNode(name);
}


GameObject* LocoMotor::Scene::GetObjectByName(std::string name) {
	if(_gameObjList.count(name) == 0)
		return nullptr;
	return _gameObjList[name];
}


GameObject* LocoMotor::Scene::GetCamera() {
	return _camera_gObj;
}

void LocoMotor::Scene::SetCamObj(GameObject* cam) {
	_camera_gObj = cam;
}



