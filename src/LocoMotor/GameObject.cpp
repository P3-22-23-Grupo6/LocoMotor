#include "GameObject.h"

//HITO 1 POC
#include "InputManager.h"


using namespace LocoMotor;

// Constructor
GameObject::GameObject() {
	_tr.direction = LMQuaternion();
	_tr.position = LMVector3();
	_tr.rotation = LMVector3();
	_tr.scale = LMVector3();
}

// Update the GameObject
void GameObject::update(float dt) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		it->second->Update(dt);
	}

	if (InputManager::Get()->GetKey(SDL_SCANCODE_A)) {
		_rigidBody->AddForce(LMVector3(1, 0, 0));
	}
	else if (InputManager::Get()->GetKey(SDL_SCANCODE_S)) {
		_rigidBody->setRotation(LMQuaternion(1, 1, 0, 0));
	}
}

// Set the position of the GameObject
void GameObject::SetPosition(LMVector3 pos) {
	_tr.position = pos;
}
// Set the rotation of the GameObject
void GameObject::SetRotation(LMVector3 rot) {
	_tr.rotation = rot;
}

// Set the transform direction of the GameObject
void GameObject::SetDirection(LMQuaternion dir) {
	_tr.direction = dir;
}

// Set the scale of the GameObject
void GameObject::SetScale(LMVector3 sc) {
	_tr.scale = sc;
}
// Get the transform of the GameObject
Transform GameObject::GetTransform() {
	return _tr;
}

//HITO 1 POC
// Set the rigid body of the GameObject
void LocoMotor::GameObject::SetRigidBody(PhysicsWrapper::BulletRigidBody* rb) {
	_rigidBody = rb;
}
// Set the renderer of the GameObject
void LocoMotor::GameObject::SetRenderer(OgreWrapper::Renderer3D* renderer) {
	_renderer = renderer;
}



// Destructor
GameObject::~GameObject() {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}