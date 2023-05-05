#include "Component.h"
#include "GameObject.h"



LocoMotor::GameObject* LocoMotor::Component::GetContext() {
	return gameObject;
}

void LocoMotor::Component::SetContext(GameObject* ent) {
	this->gameObject = ent;
}


void LocoMotor::Component::SetActive(bool active) {
	if (active && !_enabled) {
		_enabled = active;
		OnEnable();
	}
	else if (!active && _enabled) {
		_enabled = active;
		OnDisable();
	}
}


bool LocoMotor::Component::isEnabled() {
	return _enabled;
}


LocoMotor::Component::Component()
{
	gameObject = nullptr;
	_enabled = true;
}
