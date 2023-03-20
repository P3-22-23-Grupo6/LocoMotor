#include "Component.h"

void LocoMotor::Component::SetContext (GameObject* ent) {
	this->ent = ent;
}

LocoMotor::GameObject* LocoMotor::Component::GetContext() {
	return ent;
}