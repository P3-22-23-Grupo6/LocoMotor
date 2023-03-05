#include "GameObject.h"

//HITO 1 POC
#include "InputManager.h"


using namespace LocoMotor;

/// <summary>
/// Instantiates a GameObject with its trasform set to the default values.
/// </summary>
GameObject::GameObject () {
	_tr.direction = LMQuaternion ();
	_tr.position = LMVector3 ();
	_tr.rotation = LMVector3 ();
	_tr.scale = LMVector3 ();
}

/// <summary>
/// Updates all components in the GameObject.
/// </summary>
/// <param name="dt">Delta Time for each update</param>
void GameObject::update(float dt) {
	/*std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		it->second->Update (dt);
	}*/

	if (InputManager::Get()->GetKey(SDL_SCANCODE_A)) {
		_rigidBody->AddForce(LMVector3::LmToBullet(LMVector3(1, 0, 0)));
	}
	else if (InputManager::Get()->GetKey(SDL_SCANCODE_S)) {
		
	}
}

void GameObject::SetDirection (LMQuaternion dir) {
	_tr.direction = dir;
}

void LocoMotor::GameObject::SetRigidBody(BulletWrapper::BulletRigidBody* rb) {
	_rigidBody = rb;
}

void LocoMotor::GameObject::SetRenderer(OgreWrapper::Renderer3D* renderer) {
	_renderer = renderer;
}

void GameObject::SetPosition (LMVector3 pos) {
	_tr.position = pos;
}

void GameObject::SetRotation (LMVector3 rot) {
	_tr.rotation = rot;
}

void GameObject::SetScale (LMVector3 sc) {
	_tr.scale = sc;
}

Transform GameObject::GetTransform() {
	return _tr;
}




/// <summary>
/// Deletes the GameObject along all its entities
/// </summary>
GameObject::~GameObject () {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin (); it != _componentsByName.end (); it = _componentsByName.erase (it)) {
		delete it->second;
	}
}