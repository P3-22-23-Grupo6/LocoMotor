#include "Component.h"
#include "GameObject.h"


LocoMotor::GameObject* LocoMotor::Component::GetContext() {
	return gameObject;
}
void LocoMotor::Component::SetContext(GameObject* ent) {
	this->gameObject = ent;
}

void LocoMotor::Component::SetActive(bool active) {
	if (active && !enabled) {
		enabled = active;
		OnEnable();
	}
	else if (!active && enabled) {
		enabled = active;
		OnDisable();
	}
}

bool LocoMotor::Component::isEnabled() {
	return enabled;
}

LocoMotor::Component::Component()
{
	gameObject = nullptr;
	enabled = true;
}
