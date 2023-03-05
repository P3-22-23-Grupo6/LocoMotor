#include "Scene.h"
#include "Camera.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"

Scene::Scene(std::string nombre) {
	_name = nombre;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);
	SetSceneCam(_renderScn->CreateCamera("ScnCam"));

}

Scene::~Scene() {
}


void Scene::Start() {
	_isActiveScene = true;

}

void Scene::Update() {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;

	}
	//for(auto obj : _gameObjList){
		// 
		// obj->Update()
		//  }


}
void Scene::Render() {


}

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

void Scene::SetSceneCam(OgreWrapper::Camera* camera) {
	_cam = camera;
	_nod = _renderScn->CreateNode("ScnNode");

	_nod->Attach(_cam);
	//mCamNode->Attach (cam2);
	_nod->Translate(0, 10, 20);
	_nod->LookAt(0, 0, -5);
	_renderScn->SetActiveCamera(_cam);

}

/*void Scene::addObject(GameObject* obj){

	_gameObjList.push_back(obj);

}
*/
