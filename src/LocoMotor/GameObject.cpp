#include "GameObject.h"
#include "Transform.h"

//HITO 1 POC
#include "InputManager.h"
#include "LMInputs.h"
#include "Scene.h"
#include "Node.h"
#include "LogSystem.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject(OgreWrapper::Node* node) {
	_scene = nullptr;
	_transform = nullptr;
	_renderer = nullptr;
	_node = node;
	_componentsByName = {};

	physicsBasedMovement = true;
}

void LocoMotor::GameObject::PreUpdate(float dt)
{
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->PreUpdate(dt);
	}
}

void GameObject::Update(float dt) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->Update(dt);
	}
}

void LocoMotor::GameObject::AddComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params) {
	if (_componentsByName.count(name) > 0) {
		return;
	}
	Component* comp = ComponentsFactory::GetInstance()->CreateComponent(name);
	if (comp == nullptr) {
		LocoMotor::LogSystem::GetInstance()->Save(0, "Componente '" + name + "' no existe");
		return;
	}
	comp->SetContext(this);
	comp->Init(params);
	_componentsByName.insert({ name, comp });
	if (name == "Transform") {
		_transform = dynamic_cast<Transform*>(comp);
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

void GameObject::SetPosition(LMVector3 pos) {
	_transform->SetPosition(pos);
}

void LocoMotor::GameObject::SetRotation(LMQuaternion rot) {
	_transform->SetRotation(rot);
}


void GameObject::SetScale(LMVector3 sc) {
	_transform->SetSize(sc);
}



Transform* GameObject::GetTransform() {
	return _transform;
}

std::string LocoMotor::GameObject::GetName() {
	return _node->GetName();
}


void LocoMotor::GameObject::SetRenderer(OgreWrapper::Node* node) {
	_node = node;
}


void LocoMotor::GameObject::SetContext(Scene* scn) {
	_scene = scn;
}


Scene* LocoMotor::GameObject::GetScene() {
	return _scene;
}


void GameObject::StartComp() {
	for (auto& comp : _componentsByName) {
		comp.second->PreStart();
	}
	for (auto& comp : _componentsByName) {
		comp.second->Start();
	}
}


void LocoMotor::GameObject::RegisterTransform(Transform* newTrans) {
	_transform = newTrans;
}

GameObject::~GameObject() {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}