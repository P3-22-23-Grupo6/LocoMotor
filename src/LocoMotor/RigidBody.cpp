#include "RigidBody.h"
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


LocoMotor::RigidBody::RigidBody()
{
	_mass = 0;
	_damping = 0.9f;
	_angDamping = 0.7f;
	_gravity = true;
	_body = nullptr;
	_ms = nullptr;
}


void LocoMotor::RigidBody::Start(float mass)
{
	_mass = mass;
}


LocoMotor::RigidBody::~RigidBody() {
	delete _ms;
	if (_body == nullptr)return;
	PhysicsManager::GetInstance()->RemoveRigidBodyFromWorld(_body);
	if (_body && _body->getMotionState()) {
		delete _body->getMotionState();
	}
	delete _body->getCollisionShape();
	delete _body;
}


void LocoMotor::RigidBody::AddForce(LMVector3 force)
{
	_body->applyCentralForce(LmToBullet(force));
}


void LocoMotor::RigidBody::PreStart() {
	
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LmToBullet(LMVector3(0,0,0));
	info.origin = LmToBullet(gameObject->GetTransform()->GetPosition());
	info.sphereSize = 5;
	info.capsuleHeight = 10;
	info.capsuleRadius = 3;
	if (_mass == 0) {
		MeshRenderer* mR = gameObject->GetComponent<MeshRenderer>();
		if (mR == nullptr)return;
		OgreWrapper::Renderer3D* mesh = gameObject->GetComponent<MeshRenderer>()->GetRenderer();
		if (mesh != nullptr) {
			_ms = new MeshStrider(mesh->GetMesh());
			_body = PhysicsManager::GetInstance()->CreateRigidBody(info, _ms);
			_body->setUserPointer(gameObject);
			if (_raycast) UseItAsRaycast();
			if (_beATrigger) BeATrigger();
			//delete ms;
			return;
		}	
	}
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
	_body->setUserPointer(gameObject);
	if (_raycast) UseItAsRaycast();
	if (_beATrigger) BeATrigger();
}



void LocoMotor::RigidBody::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "mass") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_mass = num;
		}
		else if (params[i].first == "damping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_damping = num;
		}
		else if (params[i].first == "angDamping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_angDamping = num;
		}
		else if (params[i].first == "gravity") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_gravity = num;
		}
		else if (params[i].first == "usedAsRaycast") {
			_raycast = true;
		}
		else if (params[i].first == "isTrigger") {
			_beATrigger = true;
		}
	}
	
}


void LocoMotor::RigidBody::PreUpdate(float dt) {

	if (_body == nullptr)return;
	gameObject->SetPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	gameObject->SetRotation(BulletToLm(_body->getWorldTransform().getRotation()));
	//_body->clearForces(); // :TODO
}



void LocoMotor::RigidBody::SetRotation(LMQuaternion rot)
{
	_body->getWorldTransform().setRotation(LmToBullet(rot));
}


void LocoMotor::RigidBody::SetPosition(LMVector3 pos)
{
	_body->getWorldTransform().setOrigin(LmToBullet(pos));
}


void LocoMotor::RigidBody::UseGravity(LMVector3 gravity) {

	_body->setGravity(LmToBullet(gravity));
}


void LocoMotor::RigidBody::FreezePosition(LMVector3 freezeAxis) {
	_body->setLinearFactor(LmToBullet(freezeAxis));
}


void LocoMotor::RigidBody::FreezeRotation(LMVector3 freezeAxis) {
	_body->setAngularFactor(LmToBullet(freezeAxis));
}


bool LocoMotor::RigidBody::CheckCollision(GameObject* other) {
	if (other != nullptr) {
		return _body->checkCollideWith(other->GetComponent<RigidBody>()->GetBody());
	}
	return false;
}


btRigidBody* LocoMotor::RigidBody::GetBody() {
	return _body;
}

void LocoMotor::RigidBody::BeATrigger()
{
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}



bool LocoMotor::RigidBody::GetRaycastHit(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->CreateRaycast(from,to).hasHit;
}


LMVector3 LocoMotor::RigidBody::GetraycastHitPoint(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->CreateRaycast(from, to).hitPos;
}


LMVector3 LocoMotor::RigidBody::GethasRaycastHitNormal(LMVector3 from, LMVector3 to){
	return PhysicsManager::GetInstance()->CreateRaycast(from, to).hitVNormal;
}


void LocoMotor::RigidBody::SetCollisionGroup(int group)
{
	btBroadphaseProxy* proxy= _body->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;
}


int LocoMotor::RigidBody::GetCollisionGroup()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterGroup;
}


void LocoMotor::RigidBody::SetCollisionMask(int mask)
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterMask = 1<<mask;
}


int LocoMotor::RigidBody::GetCollisionMask()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterMask;
}


LMVector3 LocoMotor::RigidBody::GetLinearVelocity() {
	return BulletToLm(_body->getLinearVelocity()) ;
}
void LocoMotor::RigidBody::SetLinearVelocity(LMVector3 newLinearVelocity) {
	_body->setLinearVelocity(LmToBullet(newLinearVelocity));
}


LMVector3 LocoMotor::RigidBody::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}


LMVector3 LocoMotor::RigidBody::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}


LMVector3 LocoMotor::RigidBody::GetAngularVelocity() {
	return BulletToLm(_body->getAngularVelocity());
}


void LocoMotor::RigidBody::SetAngularVelocity(LMVector3 newAngularVelocity) {
	_body->setAngularVelocity(LmToBullet(newAngularVelocity));
}


void LocoMotor::RigidBody::ApplyTorqueImpulse(LMVector3 impulse) {
	_body->applyTorqueImpulse(LmToBullet(impulse));
}


void LocoMotor::RigidBody::SetFriction(float fric) {
	_body->setFriction(fric);
}

void LocoMotor::RigidBody::UseItAsRaycast() {
	SetCollisionGroup(10);
}

void LocoMotor::RigidBody::SetActivationState(ActiveState newState) {
	_body->setActivationState(newState);
}
