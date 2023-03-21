#include "Component.h"

void LocoMotor::Component::SetContext (GameObject* ent) {
	this->gameObject = ent;
}