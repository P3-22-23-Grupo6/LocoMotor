#include "RigidBodyComponent.h"
#include "LMVector.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer3D.h"
#include "MeshRenderer.h"
#include "MeshStrider.h"
#include "LmVectorConverter.h"
using namespace PhysicsWrapper;
using namespace LocoMotor;


LocoMotor::RigidBodyComponent::RigidBodyComponent()
{
	_mass = 0;
	_damping = 0.9f;
	_angDamping = 0.7f;
	_gravity = true;
	_body = nullptr;
	_ms = nullptr;
}


void LocoMotor::RigidBodyComponent::Start(float mass)
{
	_mass = mass;
}


LocoMotor::RigidBodyComponent::~RigidBodyComponent() {
	delete _ms;
	PhysicsManager::GetInstance()->RemoveRigidBodyFromWorld(_body);
	if (_body && _body->getMotionState()) {
		delete _body->getMotionState();
	}
	delete _body->getCollisionShape();
	delete _body;
}


void LocoMotor::RigidBodyComponent::addForce(LMVector3 force)
{
	_body->applyCentralForce(LmToBullet(force));
}


void LocoMotor::RigidBodyComponent::PreStart() {
	
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LmToBullet(LMVector3(0,0,0));
	info.origin = LmToBullet(gameObject->GetTransform()->GetPosition());
	info.sphereSize = 5;
	info.capsuleHeight = 10;
	info.capsuleRadius = 3;
	if (_mass == 0) {
		OgreWrapper::Renderer3D* mesh = gameObject->GetComponent<MeshRenderer>()->GetRenderer();
		if (mesh != nullptr) {
			_ms = new MeshStrider(mesh->GetMesh());
			_body = PhysicsManager::GetInstance()->CreateRigidBody(info, _ms);
			_body->setUserPointer(gameObject);
			if (_raycast) UseItAsRaycast();
			//delete ms;
			return;
		}	
	}
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
	_body->setUserPointer(gameObject);
	SetCollisionGroup(1);
	SetCollisionMask(1);
	if (_raycast) UseItAsRaycast();
}



void LocoMotor::RigidBodyComponent::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "mass") {
			_mass = std::stof(params[i].second);
		}
		else if (params[i].first == "damping") {
			_damping = std::stof(params[i].second);
		}
		else if (params[i].first == "angDamping") {
			_angDamping = std::stof(params[i].second);
		}
		else if (params[i].first == "gravity") {
			_gravity = std::stoi(params[i].second);
		}
		else if (params[i].first == "usedAsRaycast") {
			_raycast = true;
		}
	}
	
}


void LocoMotor::RigidBodyComponent::PreUpdate(float dt) {

	gameObject->SetPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	gameObject->SetRotation(BulletToLm(_body->getWorldTransform().getRotation()));
	//_body->clearForces(); // :TODO
}



void LocoMotor::RigidBodyComponent::setRotation(LMQuaternion rot)
{
	_body->getWorldTransform().setRotation(LmToBullet(rot));
}


void LocoMotor::RigidBodyComponent::setPosition(LMVector3 pos)
{
	_body->getWorldTransform().setOrigin(LmToBullet(pos));
}


void LocoMotor::RigidBodyComponent::useGravity(LMVector3 gravity) {

	_body->setGravity(LmToBullet(gravity));
}


void LocoMotor::RigidBodyComponent::FreezePosition(LMVector3 freezeAxis) {
	_body->setLinearFactor(LmToBullet(freezeAxis));
}


void LocoMotor::RigidBodyComponent::FreezeRotation(LMVector3 freezeAxis) {
	_body->setAngularFactor(LmToBullet(freezeAxis));
}


bool LocoMotor::RigidBodyComponent::checkCollision(GameObject* other) {
	if (other != nullptr) {
		return _body->checkCollideWith(other->GetComponent<RigidBodyComponent>()->getBody());
	}
	return false;
}


btRigidBody* LocoMotor::RigidBodyComponent::getBody() {
	return _body;
}

void LocoMotor::RigidBodyComponent::beATrigger()
{
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}



bool LocoMotor::RigidBodyComponent::GetRaycastHit(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from,to).hasHit;
}


LMVector3 LocoMotor::RigidBodyComponent::GetraycastHitPoint(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitPos;
}


LMVector3 LocoMotor::RigidBodyComponent::GethasRaycastHitNormal(LMVector3 from, LMVector3 to){
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitVNormal;
}


void LocoMotor::RigidBodyComponent::SetCollisionGroup(int group)
{
	btBroadphaseProxy* proxy= _body->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;
}


int LocoMotor::RigidBodyComponent::GetCollisionGroup()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterGroup;
}


void LocoMotor::RigidBodyComponent::SetCollisionMask(int mask)
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterMask = 1<<mask;
}


int LocoMotor::RigidBodyComponent::GetCollisionMask()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterMask;
}


LMVector3 LocoMotor::RigidBodyComponent::GetLinearVelocity() {
	return BulletToLm(_body->getLinearVelocity()) ;
}
void LocoMotor::RigidBodyComponent::SetLinearVelocity(LMVector3 newLinearVelocity) {
	_body->setLinearVelocity(LmToBullet(newLinearVelocity));
}


LMVector3 LocoMotor::RigidBodyComponent::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}


LMVector3 LocoMotor::RigidBodyComponent::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}


LMVector3 LocoMotor::RigidBodyComponent::GetAngularVelocity() {
	return BulletToLm(_body->getAngularVelocity());
}


void LocoMotor::RigidBodyComponent::SetAngularVelocity(LMVector3 newAngularVelocity) {
	_body->setAngularVelocity(LmToBullet(newAngularVelocity));
}


void LocoMotor::RigidBodyComponent::ApplyTorqueImpulse(LMVector3 impulse) {
	_body->applyTorqueImpulse(LmToBullet(impulse));
}


void LocoMotor::RigidBodyComponent::SetFriction(float fric) {
	_body->setFriction(fric);
}

void LocoMotor::RigidBodyComponent::UseItAsRaycast() {
	SetCollisionGroup(10);
}

void LocoMotor::RigidBodyComponent::SetActivationState(ActiveState newState) {
	_body->setActivationState(newState);
}
