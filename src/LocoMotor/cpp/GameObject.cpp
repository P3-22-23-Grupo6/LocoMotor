#include "GameObject.h"
#include "Transform.h"
#include "LogSystem.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject(const std::string& name) {
	_scene = nullptr;
	_transform = nullptr;
	_componentsByName = {};
	_gobjName = name;
}

void GameObject::Update(float dt) {

	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->PreUpdate(dt);
	}
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->Update(dt);
	}
	if (_transform->GetPosition().Magnitude() > DBL_MAX / 1.5) {
		_transform->SetPosition(LMVector3());
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
	return _gobjName;
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