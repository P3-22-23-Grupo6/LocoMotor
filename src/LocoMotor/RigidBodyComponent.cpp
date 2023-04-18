#include "RigidBodyComponent.h"
#include "LMVector.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Renderer3D.h"
#include "MeshRenderer.h"
#include "MeshStrider.h"
using namespace PhysicsWrapper;
using namespace LocoMotor;

const std::string RigidBodyComponent::name = "RigidBodyComponent";

LocoMotor::RigidBodyComponent::RigidBodyComponent()
{
	_mass = 0;
	_damping = 0.9;
	_angDamping = 0.7;
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
	_body->applyCentralForce(LMVector3::LmToBullet(force));
}
void LocoMotor::RigidBodyComponent::Start() {
	
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LMVector3::LmToBullet(LMVector3(12,3,5));
	info.origin = LMVector3::LmToBullet(gameObject->GetTransform().position);
	info.size = -1;
	if (_mass == 0) {
		OgreWrapper::Renderer3D* mesh = gameObject->GetComponent<MeshRenderer>()->GetRenderer();
		if (mesh != nullptr) {
			_ms = new MeshStrider(mesh->GetMesh());
			_body = PhysicsManager::GetInstance()->CreateRigidBody(info, _ms);
			//delete ms;
			return;
		}	
	}
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
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
	gameObject->SetPosition(LMVector3::BulletToLm(_body->getWorldTransform().getOrigin()));
	_body->clearForces();
}


void LocoMotor::RigidBodyComponent::setRotation(LMQuaternion rot)
{
	_body->getWorldTransform().setRotation(LMQuaternion::LmToBullet(rot));
}

void LocoMotor::RigidBodyComponent::useGravity(LMVector3 gravity) {

	_body->setGravity(LMVector3::LmToBullet(gravity));
}

void LocoMotor::RigidBodyComponent::FreezePosition(LMVector3 freezeAxis) {
	_body->setLinearFactor(LMVector3::LmToBullet(freezeAxis));
}

void LocoMotor::RigidBodyComponent::FreezeRotation(LMVector3 freezeAxis) {
	_body->setAngularFactor(LMVector3::LmToBullet(freezeAxis));
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

bool LocoMotor::RigidBodyComponent::GetRaycastHit(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from,to).hasHit;
}

LMVector3 LocoMotor::RigidBodyComponent::GetraycastHitPoint(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitPos;
}

LMVector3 LocoMotor::RigidBodyComponent::GethasRaycastHitNormal(LMVector3 from, LMVector3 to){
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitVNormal;
}
