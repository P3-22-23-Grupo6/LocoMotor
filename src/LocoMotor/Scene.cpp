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
/**
 * The Scene constructor creates a new scene and adds a camera game object with transform, camera, and
 * audio listener components.
 * @brief Scene constructor.
 * @param nombre "nombre" is a string parameter that represents the name of the scene being created.
 */
Scene::Scene(std::string nombre) {
	_name = nombre;
	_renderScn = OgreWrapper::OgreManager::GetInstance()->CreateScene(_name);

	// Crear camara
	camera_gObj = AddGameobject("cam");
	camera_gObj->AddComponent("Transform");
	camera_gObj->AddComponent("Camera");
	camera_gObj->AddComponent("AudioListener");
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


/**
 * The Start function initializes components for all game objects in the scene and sets the scene as
 * active.
 */
void Scene::Start() {

	//GameObject* camera = new GameObject();

	for (auto& obj : _gameObjList) {
		obj.second->StartComp();
	}

	_isActiveScene = true;

	//camera->AddComponent();
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

/**
 * This function updates all game objects in the scene and sets the camera position based on the
 * position of a specific game object.
 * 
 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
 * used to ensure that the game runs at a consistent speed regardless of the performance of the
 * computer running it.
 */
void Scene::Update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;

	}
	for (auto& obj : _gameObjList) {

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
/**
 * This function renders the scene using OgreWrapper and _renderScn.
 */
void Scene::Render() {
	_renderScn->Render();
	OgreWrapper::OgreManager::GetInstance()->Render();
}

/**
 * The function DeActivate() deactivates the scene and deletes all game objects in the scene.
 * @brief Deactivate the scene and delete all game objects in the scene.
 */
void Scene::DeActivate() {
	_isActiveScene = false;
	std::unordered_map<std::string, GameObject*>::iterator it;
	for (it = _gameObjList.begin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}

}


//Activate

/**
 * The function returns the active status of a scene in C++.
 * @brief Returns the active status of a scene in C++.
 * @return the value of the private member variable `_isActiveScene`.
 */
bool Scene::GetActiveStatus() {
	return _isActiveScene;
}

/**
 * This function returns the name of a scene as a string.
 * @brief Returns the name of a scene as a string.
 * @return A string representing the name of the scene.
 */
std::string Scene::GetSceneName() {
	return _name;
}

/**
 * This function sets the camera of a scene.
 * @brief Set the camera of a scene.
 * @param camera A camara to set as the active camera of the scene.
 */
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

/**
 * The function adds a new game object to the scene or returns an existing one with the same name.
 * @brief Adds a new game object to the scene or returns an existing one with the same name.
 * @param name A string representing the name of the GameObject to be added to the Scene.
 * 
 * @return a pointer to a GameObject.
 */
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

/**
 * The function returns a GameObject pointer by searching for its name in a Scene's list of
 * GameObjects.
 * @brief Returns a GameObject pointer by searching for its name in a Scene's list of GameObjects.
 * @param name name is a string parameter that represents the name of the GameObject that is being
 * searched for in the Scene's list of GameObjects.
 * 
 * @return a pointer to a GameObject. If the GameObject with the given name exists in the _gameObjList
 * map, then a pointer to that GameObject is returned. Otherwise, a null pointer is returned.
 */
GameObject* LocoMotor::Scene::GetObjectByName(std::string name) {
	if(_gameObjList.count(name) == 0)
		return nullptr;
	return _gameObjList[name];
}

/**
 * The function returns a pointer to the camera GameObject in the Scene.
 * @brief Returns a pointer to the camera GameObject in the Scene.
 * @return A pointer to a GameObject object, specifically the camera_gObj object.
 */
GameObject* LocoMotor::Scene::GetCamera() {
	return camera_gObj;
}



