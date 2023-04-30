#include "GameObject.h"
#include "Transform.h"

//HITO 1 POC
#include "InputManager.h"
#include "LMInputs.h"
#include "Scene.h"
#include "Node.h"
//Borrar luego
#include "SceneManager.h"
#include "RigidBodyComponent.h"
#include "OpenSteer/SimpleVehicle.h"
#include "LmVectorConverter.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject(OgreWrapper::Node* node) {
	scene = nullptr;
	transform = nullptr;
	_renderer = nullptr;
	_node = node;
	_componentsByName = {};

	physicsBasedMovement = true;
	/*this->AddComponent("Transform");*/
	tiltAmount = 0.0f; //TEMPORAL
}

// Update the GameObject
void GameObject::Update(float dt) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->Update(dt);
	}


	//if (GetComponent<RigidBodyComponent>() == nullptr) return;
	//InputManager* man = InputManager::GetInstance();


	if (!movable)return;

	RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
}


void LocoMotor::GameObject::AddComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params) {
	if (_componentsByName.count(name) > 0) {
		return;
	}
	Component* comp = ComponentsFactory::GetInstance()->CreateComponent(name);
	comp->SetContext(this);
	comp->Init(params);
	_componentsByName.insert({ name, comp });
	if (name == "Transform") {
		transform = dynamic_cast<Transform*>(comp);
	}
}


void LocoMotor::GameObject::OnCollisionEnter(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionEnter(other);
	}
}

void LocoMotor::GameObject::OnCollisionExit(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionExit(other);
	}
}

void LocoMotor::GameObject::OnCollisionStay(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionStay(other);
	}
}

// Set the position of the GameObject
void GameObject::SetPosition(LMVector3 pos) {
	transform->SetPosition(pos);
}

void LocoMotor::GameObject::SetRotation(LMQuaternion rot) {
	transform->SetRotation(rot);
}

// Set the scale of the GameObject
void GameObject::SetScale(LMVector3 sc) {
	transform->SetSize(sc);
}

// Get the transform of the GameObject
Transform* GameObject::GetTransform() {
	return transform;
}

std::string LocoMotor::GameObject::GetName() {
	return _node->GetName();
}

// Set the renderer of the GameObject
void LocoMotor::GameObject::SetRenderer(OgreWrapper::Node* node) {
	_node = node;
}

void LocoMotor::GameObject::SetContext(Scene* scn) {
	scene = scn;
}

Scene* LocoMotor::GameObject::GetScene() {
	return scene;
}

void GameObject::StartComp() {
	for (auto& comp : _componentsByName) {
		comp.second->Start();
	}
}

void LocoMotor::GameObject::RegisterTransform(Transform* newTrans) {
	transform = newTrans;
}


// Destructor
GameObject::~GameObject() {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}