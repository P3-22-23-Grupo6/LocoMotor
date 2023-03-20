#include "RigidBodyComponent.h"
#include "lmVector.h"
#include "BulletRigidBody.h"
#include "PhysicsManager.h"

LocoMotorComponent::RigidBodyComponent::RigidBodyComponent() {
	PhysicsWrapper::RigidBodyInfo info;
	PhysicsWrapper::PhysicsManager::GetInstance()->CreateRigidBody(info);
}

LocoMotorComponent::RigidBodyComponent::~RigidBodyComponent() {
}

void LocoMotorComponent::RigidBodyComponent::setMass() {
}

void LocoMotorComponent::RigidBodyComponent::useGravity(bool gravity) {
}

void LocoMotorComponent::RigidBodyComponent::FreezePosition(LMVector3 freezeAxis) {
}

void LocoMotorComponent::RigidBodyComponent::FreezeRotation(LMVector3 freezeAxis) {
}

void LocoMotorComponent::RigidBodyComponent::setDynamic() {
}

void LocoMotorComponent::RigidBodyComponent::setKinematic() {
}

void LocoMotorComponent::RigidBodyComponent::setStatic() {
}
