#include "Scene.h"
#include "Camera.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Renderer3D.h"
#include "RigidBodyComponent.h"
#include "PhysicsManager.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "GameObject.h"

using namespace LocoMotor;
Scene::Scene(std::string nombre) {
	_name = nombre;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);

	// Crear camara
	camera_gObj = AddGameobject("cam");
	camera_gObj->AddComponent("Transform");
	camera_gObj->AddComponent("Camera");
	//camera_gObj->AddComponent("AudioListener");
	//_currentCam = cam_Obj->AddComponent<LM_Component::Camera>();

	/*SetSceneCam(_renderScn->CreateCamera("ScnCam"));*/
}

Scene::~Scene() {
	std::unordered_map<std::string, GameObject*>::const_iterator it;
	for (it = _gameObjList.cbegin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}
	_renderScn = nullptr;
	_cam = nullptr;
	_nod = nullptr;
}


void Scene::Start() {

	//GameObject* camera = new GameObject();

	for (auto obj : _gameObjList) {
		obj.second->StartComp();
	}

	_isActiveScene = true;

	// TODO: camera->AddComponent();
	//GameObject* map = AddGameobject("map");
	//map->AddComponent<MeshRenderer>("map", "Track.mesh", "FalconRedone/FalconMat", _renderScn);
	//map->AddComponent<RigidBodyComponent>(0);

	//_isActiveScene = true;
	//
	//  = AddGameobject("ship");
	//ship_gObj->AddComponent<MeshRenderer>("ship", "BlueFalcon.mesh", "FalconRedone/FalconMat", _renderScn);
	//ship_gObj->AddComponent<ParticleSystem>("smoke", _renderScn, "Racers/Smoke");
	//ship_gObj->AddComponent<ParticleSystem>("fire", _renderScn, "Racers/Fire");	

	//ship_gObj->AddComponent<RigidBodyComponent>(1);
	////_gameObjList.push_back(ship_gObj);

	////ship_gObj->SetRigidBody(PhysicsWrapper::PhysicsManager::GetInstance()->CreateRigidBody(rb));
	////rend->SetMaterial("Racers/Falcon");
	//ship_gObj->GetNode()->SetScale(10.0f, 10.0f, 10.0f);
	////ship_gObj->GetNode()->SetPosition(0, 1000.0f, 0);
	//ship_gObj->SetPosition(LMVector3(0, 10, 0));
	//ship_gObj->setMovable(true);


	////// CHECKPOINT

	//GameObject* checkpoint = AddGameobject("checkpoint");
	//checkpoint->AddComponent<MeshRenderer>("checkpoint", "BlueFalcon.mesh", "FalconRedone/FalconMat", _renderScn);
	//checkpoint->AddComponent<RigidBodyComponent>(0);
	//checkpoint->GetNode()->SetScale(60.0f, 10.0f, 10.0f);
	//checkpoint->SetPosition(LMVector3(0, 5, -50));
	//checkpoint->AddComponent<Checkpoint>(ship_gObj, 0);



	//_renderScn->Prueba();
	////Skybox
	//_renderScn->SetSkybox();

	//for (auto obj : _gameObjList) {
	//	obj->StartComp();
	//}

	//camera_gObj->GetComponent<Camera>()->SetTarget(ship_gObj, LMVector3(0, 5, 15));
	////ship_gObj->GetComponent<RigidBodyComponent>()
	//map->GetComponent<RigidBodyComponent>()->FreezePosition(LMVector3(1, 0, 1));
	//map->GetComponent<RigidBodyComponent>()->setStatic();
}

void Scene::Update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;

	}
	for (auto obj : _gameObjList) {

		obj.second->Update(dt);

		//float x = ship_gObj->GetNode()->GetPosition_X();
		//float y = ship_gObj->GetNode()->GetPosition_Y();
		//float z = ship_gObj->GetNode()->GetPosition_Z();
		//camera_gObj->SetPosition(LMVector3(x, y + 10, z + 50));
		////_nod->SetPosition(node->GetPosition_X(), node->GetPosition_Y() + 10, node->GetPosition_Z() + 15);

		//LMVector3 pos = camera_gObj->GetTransform().position;

		////std::cout << "CAMERAPOSITION_GAMEOBJ = " << pos.GetX() << ", " << pos.GetY() << ", " << pos.GetZ() << "\n";

		////std::cout << "CARPOSITION_NODE = " << x << ", " << y << ", " << z << "\n";
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
	if (_gameObjList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjList[name];	
	}
	OgreWrapper::Node* newNode = _renderScn->CreateNode(name);
	GameObject* newObj = new GameObject(newNode);
	newObj->SetContext(this);
	_gameObjList.insert({ name, newObj });
	return newObj;
}

GameObject* LocoMotor::Scene::GetObjectByName(std::string name) {
	if(_gameObjList.count(name) == 0)
		return nullptr;
	return _gameObjList[name];
}

OgreWrapper::RenderScene* LocoMotor::Scene::GetRender() {
	return _renderScn;
}

GameObject* LocoMotor::Scene::GetCamera() {
	return camera_gObj;
}



