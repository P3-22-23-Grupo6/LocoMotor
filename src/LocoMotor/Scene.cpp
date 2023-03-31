#include "Scene.h"
#include "Camera.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "GameObject.h"
#include "Renderer3D.h"
#include "RigidBodyComponent.h"
#include "PhysicsManager.h"
#include "MeshRederer.h"
#include "ParticleSystem.h"

using namespace LocoMotor;
Scene::Scene(std::string nombre) {
	_name = nombre;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);

	// Crear camara
	camera_gObj = AddGameobject("cam");
	camera_gObj->AddComponent<LocoMotor::Camera>(this, _renderScn);
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
	GameObject* map = AddGameobject("map");
	map->AddComponent<MeshRenderer>("map", "Track.mesh", "FalconRedone/FalconMat", _renderScn);
	map->AddComponent<RigidBodyComponent>(0);

	_isActiveScene = true;
	ship_gObj = AddGameobject("ship");
	ship_gObj->AddComponent<MeshRenderer>("ship", "BlueFalcon.mesh", "FalconRedone/FalconMat", _renderScn);
	ship_gObj->AddComponent<ParticleSystem>("smoke", _renderScn, "Racers/Smoke");
	ship_gObj->AddComponent<ParticleSystem>("fire", _renderScn, "Racers/Fire");	

	ship_gObj->AddComponent<RigidBodyComponent>(1);
	//_gameObjList.push_back(ship_gObj);

	//ship_gObj->SetRigidBody(PhysicsWrapper::PhysicsManager::GetInstance()->CreateRigidBody(rb));
	//rend->SetMaterial("Racers/Falcon");
	ship_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	//ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	ship_gObj->SetPosition(LMVector3(0, 10, 0));
	ship_gObj->setMovable(true);
	_renderScn->Prueba();
	//Skybox
	_renderScn->SetSkybox();

	for (auto obj : _gameObjList) {
		obj->StartComp();
	}

	camera_gObj->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 5, 15));
	//ship_gObj->GetComponent<RigidBodyComponent>()
	map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
	map->GetComponent<RigidBodyComponent>()->setStatic();
}

void Scene::Update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;

	}
	for (auto obj : _gameObjList) {

		obj->Update(dt);

		float x = ship_gObj->GetNode()->GetPosition_X();
		float y = ship_gObj->GetNode()->GetPosition_Y();
		float z = ship_gObj->GetNode()->GetPosition_Z();
		camera_gObj->SetPosition(LMVector3(x, y + 10, z + 50));
		//_nod->SetPosition(node->GetPosition_X(), node->GetPosition_Y() + 10, node->GetPosition_Z() + 15);

		LMVector3 pos = camera_gObj->GetTransform().position;

		std::cout << "CAMERAPOSITION_GAMEOBJ = " << pos.GetX() << ", " << pos.GetY() << ", " << pos.GetZ() << "\n";

		//std::cout << "CARPOSITION_NODE = " << x << ", " << y << ", " << z << "\n";
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
	//_nod = _renderScn->CreateNode("ScnNode");

	// Acceder al RenderEntity de la camara
	//OgreWrapper::RenderEntity* renderObj = (OgreWrapper::RenderEntity*) _cam;
	//_nod->Attach(renderObj);
	//mCamNode->Attach (cam2);
	//_nod->Translate(0, 10, 20);
	//_nod->LookAt(0, 0, -5);
	_renderScn->SetActiveCamera(_cam);
}

GameObject* LocoMotor::Scene::AddGameobject(std::string name) {
	OgreWrapper::Node* newNode = _renderScn->CreateNode(name);
	GameObject* newObj = new GameObject(newNode);
	AddObject(newObj);
	return newObj;
}

void Scene::AddObject(GameObject* obj) {
	_gameObjList.push_back(obj);
}



