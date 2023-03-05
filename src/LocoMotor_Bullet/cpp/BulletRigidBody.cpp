#include "BulletRigidBody.h"
#include "PhysicsManager.h"
#include <btBulletDynamicsCommon.h>
#include "lmVector.h"
using namespace PhysicsWrapper;
BulletRigidBody::BulletRigidBody(RigidBodyInfo info) {
	if (info.size <= 0.0)
		_shape = new btBoxShape(info.boxSize);
	else
		_shape = new btSphereShape(info.size);

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

void BulletRigidBody::AddForce(btVector3 force) {
	_rigidBody->applyCentralForce(force);
}

void BulletRigidBody::setRotation(LMQuaternion rot) {
	_rigidBody->getWorldTransform().setRotation(LMQuaternion::LmToBullet(rot));
}

LMQuaternion BulletRigidBody::getRotation() {
	return LMQuaternion::BulletToLm(_rigidBody->getWorldTransform().getRotation());
}
