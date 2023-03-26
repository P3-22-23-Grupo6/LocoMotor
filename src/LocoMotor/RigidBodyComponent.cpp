#include "RigidBodyComponent.h"
#include "lmVector.h"
#include "BulletRigidBody.h"
#include "PhysicsManager.h"
using namespace PhysicsWrapper;
LocoMotor::RigidBodyComponent::RigidBodyComponent(RigidBodyInfo info) {
	_mass = info.mass;
	_damping = 0;
	_angDamping = 0;
	_gravity = true;
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
}

LocoMotor::RigidBodyComponent::~RigidBodyComponent() {
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
