#include "GameObject.h"

using namespace LocoMotor;

GameObject::GameObject () {
	_tr.direction = LMQuaternion ();
	_tr.position = LMVector3 ();
	_tr.rotation = LMVector3 ();
	_tr.scale = LMVector3 ();
}

void GameObject::SetDirection (LMQuaternion dir) {
	_tr.direction = dir;
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





GameObject::~GameObject () {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin (); it != _componentsByName.end (); it = _componentsByName.erase (it)) {
		delete it->second;
	}
}