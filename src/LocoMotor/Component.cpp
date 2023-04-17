#include "Component.h"
#include "GameObject.h"


LocoMotor::GameObject* LocoMotor::Component::GetContext() {
	return gameObject;
}
void LocoMotor::Component::SetContext(GameObject* ent) {
	this->gameObject = ent;
}

void LocoMotor::Component::InitComponent() {
}

//LocoMotor::GameObject* LocoMotor::Component::GetGameobject() 
//{ return gameObject; }
