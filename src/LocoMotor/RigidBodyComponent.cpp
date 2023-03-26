#include "RigidBodyComponent.h"
#include "lmVector.h"
#include "BulletRigidBody.h"
#include "PhysicsManager.h"
#include "GameObject.h"
using namespace PhysicsWrapper;
using namespace LocoMotor;
const std::string RigidBodyComponent::name = "RigidBodyComponent";

LocoMotor::RigidBodyComponent::RigidBodyComponent(float mass) {
	_mass = mass;
	_damping = 0.9;
	_angDamping = 0.7;
	_gravity = true;
	_body = nullptr;
}

LocoMotor::RigidBodyComponent::~RigidBodyComponent() {
}

void LocoMotor::RigidBodyComponent::addForce(LMVector3 force)
{
	_body->AddForce(force);
}
void LocoMotor::RigidBodyComponent::Start() {
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LMVector3::LmToBullet(gameObject->GetTransform().scale);
	info.origin = LMVector3::LmToBullet(gameObject->GetTransform().position);
	info.size = -1;
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
}

void LocoMotor::RigidBodyComponent::Update(float dt) {
	gameObject->SetPosition(_body->getPosition());
	//gameObject->SetRotation(_body->getRotation());
}


void LocoMotor::RigidBodyComponent::setRotation(LMQuaternion rot)
{
	_body->setRotation(rot);
}

void LocoMotor::RigidBodyComponent::setMass(float m) {
	_mass = m;
	_body->setMass(m);
}

void LocoMotor::RigidBodyComponent::useGravity(bool gravity) {
	if (gravity)
		_body->setGravity(LMVector3(0, -9.8, 0));
	else
		_body->setGravity(LMVector3(0, 0, 0));

}

void LocoMotor::RigidBodyComponent::FreezePosition(LMVector3 freezeAxis) {
	_body->FreezePosition(freezeAxis);
}

void LocoMotor::RigidBodyComponent::FreezeRotation(LMVector3 freezeAxis) {
	_body->FreezeRotation(freezeAxis);
}

void LocoMotor::RigidBodyComponent::setDynamic() {
	_body->setBodystate(0);
}

void LocoMotor::RigidBodyComponent::setKinematic() {
	_body->setBodystate(2);
}

void LocoMotor::RigidBodyComponent::setStatic() {
	_body->setBodystate(1);
}

void LocoMotor::RigidBodyComponent::setNoContactResponse() {
	_body->setBodystate(4);
}
