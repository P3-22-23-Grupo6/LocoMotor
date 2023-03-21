#include "Scene.h"
#include "Camera.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "GameObject.h"
#include "Renderer3D.h"
#include "BulletRigidBody.h"
#include "PhysicsManager.h"

using namespace LocoMotor;
Scene::Scene(std::string nombre) {
	_name = nombre;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);

	// Crear camara
	camera_gameObject = AddGameobject();
	camera_gameObject->AddComponent<LocoMotor::Camera>(this, _renderScn);
	//_currentCam = cam_Obj->AddComponent<LM_Component::Camera>();

	/*SetSceneCam(_renderScn->CreateCamera("ScnCam"));*/
}

Scene::~Scene() {
	std::vector<GameObject*>::const_iterator it;
	for (it = _gameObjList.cbegin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete* it;
	}
	_renderScn = nullptr;
	_cam = nullptr;
	_nod = nullptr;
}


void Scene::Start() {

	//GameObject* camera = new GameObject();

	// TODO: camera->AddComponent();


	_isActiveScene = true;
	GameObject* g = AddGameobject();
	node = _renderScn->CreateNode("Coche");
	OgreWrapper::Renderer3D* rend = _renderScn->CreateRenderer("Feisar.mesh");
	g->SetRenderer(rend, node);
	PhysicsWrapper::RigidBodyInfo rb;
	rb.boxSize = { 1,1,1 };
	rb.origin = { 0,0,0 };
	rb.mass = 1;
	g->SetRigidBody(PhysicsWrapper::PhysicsManager::GetInstance()->CreateRigidBody(rb));
	rend->SetMaterial("Racers/Falcon");
	node->SetScale(2.0f, 2.0f, 2.0f);
	_renderScn->Prueba();
}

void Scene::Update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;

	}
	for (auto obj : _gameObjList) {

		obj->Update(dt);

		camera_gameObject->SetPosition(LMVector3(node->GetPosition_X(), node->GetPosition_Y() + 10, node->GetPosition_Z() + 15));
		//_nod->SetPosition(node->GetPosition_X(), node->GetPosition_Y() + 10, node->GetPosition_Z() + 15);
	}
}
void Scene::Render() {
	_renderScn->Render();
	OgreWrapper::OgreManager::GetInstance()->Render();
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
	//OgreWrapper::RenderEntity* camObj = _cam;
	_nod = _renderScn->CreateNode("ScnNode");

	// Acceder al RenderEntity de la camara
	OgreWrapper::RenderEntity* renderObj = (OgreWrapper::RenderEntity*)_cam;
	//_nod->Attach(renderObj);
	//mCamNode->Attach (cam2);
	//_nod->Translate(0, 10, 20);
	//_nod->LookAt(0, 0, -5);
	_renderScn->SetActiveCamera(_cam);
}

GameObject* LocoMotor::Scene::AddGameobject() {
	OgreWrapper::Node* newNode = _renderScn->CreateNode("ScnNode");
	GameObject* newObj = new GameObject(newNode);
	AddObject(newObj);
	return newObj;
}

void Scene::AddObject(GameObject* obj) {
	_gameObjList.push_back(obj);
}

