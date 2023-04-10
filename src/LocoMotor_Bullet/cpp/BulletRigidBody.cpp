#include "BulletRigidBody.h"
#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include "LMVector.h"
#include "MeshStrider.h"
using namespace PhysicsWrapper;
BulletRigidBody::BulletRigidBody(RigidBodyInfo info, MeshStrider* mesh) {
	if (mesh != nullptr) {
		_shape = new btBvhTriangleMeshShape(mesh,true,true);
	}
	else {
		if (info.size <= 0.0)
			_shape = new btBoxShape(info.boxSize);
		else
			_shape = new btSphereShape(info.size);
	}

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(info.origin);

	btScalar mass(info.mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		_shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, _shape, localInertia);
	_rigidBody = new btRigidBody(rbInfo);

	//add the body to the dynamics world;
	PhysicsManager::GetInstance()->AddRigidBodyToWorld(_rigidBody);
	_rigidBody->setDamping(0.7, 0.7);
	if (isDynamic) {
		_rigidBody->setCcdMotionThreshold(0.0000001);
		_rigidBody->setCcdSweptSphereRadius(0.5f);
	}
}

LMVector3 PhysicsWrapper::BulletRigidBody::getPosition() {
	return LMVector3::BulletToLm(_rigidBody->getWorldTransform().getOrigin());
}

void PhysicsWrapper::BulletRigidBody::setGravity(LMVector3 gravity) {
	_rigidBody->setGravity(LMVector3::LmToBullet(gravity));
}

void PhysicsWrapper::BulletRigidBody::FreezePosition(LMVector3 axis) {
	_rigidBody->setLinearFactor(LMVector3::LmToBullet(axis));
}

void PhysicsWrapper::BulletRigidBody::FreezeRotation(LMVector3 axis) {
	_rigidBody->setAngularFactor(LMVector3::LmToBullet(axis));
}

void PhysicsWrapper::BulletRigidBody::setMass(float m) {
	_rigidBody->setMassProps(m, _rigidBody->getLocalInertia());
	if (m > 0)setBodystate(0);
}

void PhysicsWrapper::BulletRigidBody::resetBoxShapeSize(LMVector3 size) {
	if (_rigidBody->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {
		btCollisionShape* newshape = new btBoxShape(LMVector3::LmToBullet(size));
		float mass = _rigidBody->getMass();
		btVector3 localInertia(0, 0, 0);
		if (mass != 0.f)
			_shape->calculateLocalInertia(mass, localInertia);
		_rigidBody->setCollisionShape(newshape);
		_shape = newshape;
		
	}
}

void PhysicsWrapper::BulletRigidBody::resetSphereShapeSize(float size) {
	if (_rigidBody->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
		btCollisionShape* newshape = new btSphereShape(size);
		float mass = _rigidBody->getMass();
		btVector3 localInertia(0, 0, 0);
		if (mass != 0.f)
			_shape->calculateLocalInertia(mass, localInertia);
		_rigidBody->setCollisionShape(newshape);
		_shape = newshape;
	}
}

void PhysicsWrapper::BulletRigidBody::setBodystate(int state) {
	_rigidBody->setCollisionFlags(state);
}

RaycastInfo PhysicsWrapper::BulletRigidBody::createRaycast(LMVector3 from, LMVector3 direction) {
	RaycastInfo newRaycastInfo = RaycastInfo();
	
	btCollisionWorld::ClosestRayResultCallback rayCallback(LMVector3::LmToBullet(from), LMVector3::LmToBullet(direction));
	
	PhysicsManager::GetInstance()->GetDynamicWorld()->rayTest(LMVector3::LmToBullet(from), LMVector3::LmToBullet(direction), rayCallback);
	if (rayCallback.hasHit()) {
		newRaycastInfo.hasHit = true;
		newRaycastInfo.hitPos = LMVector3(rayCallback.m_hitPointWorld.getX(),
										  rayCallback.m_hitPointWorld.getY(), 
										  rayCallback.m_hitPointWorld.getZ());
		newRaycastInfo.hitVNormal = LMVector3(rayCallback.m_hitNormalWorld.getX(),
											  rayCallback.m_hitNormalWorld.getY(),
											  rayCallback.m_hitNormalWorld.getZ());
	}
	else newRaycastInfo.hasHit = false;
	return newRaycastInfo;
}

BulletRigidBody::~BulletRigidBody() {
	PhysicsManager::GetInstance()->RemoveRigidBodyFromWorld(_rigidBody);
	if (_rigidBody && _rigidBody->getMotionState()) {
		delete _rigidBody->getMotionState();
	}
	delete _rigidBody;
	_rigidBody = nullptr;
	delete _shape;
	_shape = nullptr;
}

bool PhysicsWrapper::BulletRigidBody::checkCollision(BulletRigidBody* other) {
	if (other != nullptr) {
		 return _rigidBody->checkCollideWith(other->getBody());
	}
	return false;
}

btRigidBody* PhysicsWrapper::BulletRigidBody::getBody() {
	return _rigidBody;
}

void BulletRigidBody::AddForce(LMVector3 force) {
	_rigidBody->applyCentralForce(LMVector3::LmToBullet(force));
}

void BulletRigidBody::setRotation(LMQuaternion rot) {
	_rigidBody->getWorldTransform().setRotation(LMQuaternion::LmToBullet(rot));
}

LMQuaternion BulletRigidBody::getRotation() {
	return LMQuaternion::BulletToLm(_rigidBody->getWorldTransform().getRotation());
}
