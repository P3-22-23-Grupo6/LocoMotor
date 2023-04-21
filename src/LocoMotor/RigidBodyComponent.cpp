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

const std::string RigidBodyComponent::name = "RigidBodyComponent";

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
}

void LocoMotor::RigidBodyComponent::addForce(LMVector3 force)
{
	_body->applyCentralForce(LmToBullet(force));
}
void LocoMotor::RigidBodyComponent::Start() {
	
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
			//delete ms;
			return;
		}	
	}
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
	_body->setUserPointer(gameObject);
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
	}
	_body = nullptr;
}

void LocoMotor::RigidBodyComponent::Update(float dt) {
	gameObject->SetPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	gameObject->SetRotation(BulletToLm(_body->getWorldTransform().getRotation()));
	_body->clearForces();
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

LMVector3 LocoMotor::RigidBodyComponent::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}

LMVector3 LocoMotor::RigidBodyComponent::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}

void LocoMotor::RigidBodyComponent::ApplyTorqueImpulse(LMVector3 impulse) {
	_body->applyTorqueImpulse(LmToBullet(impulse));
}

void LocoMotor::RigidBodyComponent::SetFriction(float fric) {
	_body->setFriction(fric);
}
