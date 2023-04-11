#include "RigidBodyComponent.h"
#include "LMVector.h"
#include "BulletRigidBody.h"
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
	_body->AddForce(force);
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
	gameObject->SetPosition(_body->getPosition());
	_body->clearForce();
	//gameObject->SetRotation(_body->getRotation());
	
	//LMVector3 rayFrom = LMVector3(_body->getPosition());
	//LMVector3 rayTo = LMVector3(_body->getPosition());
	////btVector3 btTo(camPos.x, -5000.0f, camPos.z);
	//btCollisionWorld::ClosestRayResultCallback res(rayFrom, rayTo);
	//Base::getSingletonPtr()->m_btWorld->rayTest(btFrom, btTo, res); // m_btWorld is btDiscreteDynamicsWorld
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
		_body->setGravity(LMVector3(0, -99, 0));
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

bool LocoMotor::RigidBodyComponent::checkCollision(GameObject* go) {
	return _body->checkCollision(go->GetComponent<RigidBodyComponent>()->getBody());
}

PhysicsWrapper::BulletRigidBody* LocoMotor::RigidBodyComponent::getBody() {
	return _body;
}	

bool LocoMotor::RigidBodyComponent::GetRaycastHit(LMVector3 from, LMVector3 to) {
	return _body->createRaycast(from, to).hasHit;
}

LMVector3 LocoMotor::RigidBodyComponent::GetraycastHitPoint(LMVector3 from, LMVector3 to) {
	return _body->createRaycast(from, to).hitPos;
}

LMVector3 LocoMotor::RigidBodyComponent::GethasRaycastHitNormal(LMVector3 from, LMVector3 to){
	return _body->createRaycast(from, to).hitVNormal;
}
