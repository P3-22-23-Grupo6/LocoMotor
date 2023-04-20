#include "PhysicsManager.h"
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "MeshStrider.h"
#include "LmVectorConverter.h"
#include "LMVector.h"
using namespace PhysicsWrapper;
PhysicsManager* Singleton<PhysicsManager>::_instance = nullptr;

PhysicsManager::PhysicsManager() {
	//Set default configuration
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_overlappingPairCache = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver;
	//Create Dynamic world
	_dynamicWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
	
	//Set default gravity
	_dynamicWorld->setGravity(btVector3(0, -98, 0));
}

PhysicsManager::~PhysicsManager() {
	for (int i = _dynamicWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = _dynamicWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		delete body->getCollisionShape();
		_dynamicWorld->removeCollisionObject(obj);
		delete obj;
	}
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _overlappingPairCache;
	delete _solver;
	delete _dynamicWorld;
}

btRigidBody* PhysicsManager::CreateRigidBody(RigidBodyInfo info, MeshStrider* ms) {
	btCollisionShape* shape=nullptr;
	if (ms != nullptr) {
		shape = new btBvhTriangleMeshShape(ms, true, true);
	}
	else {
		if (info.capsuleHeight > 0.0)
			shape = new btCapsuleShapeZ(info.capsuleRadius, info.capsuleHeight);
		else if (info.sphereSize <= 0.0)
			shape = new btBoxShape(info.boxSize);
		else if(info.sphereSize)
			shape = new btSphereShape(info.sphereSize);
	}
	if (shape == nullptr)return nullptr;
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(info.origin);

	btScalar mass(info.mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* rigidbody = new btRigidBody(rbInfo);

	//add the body to the dynamics world;
	_dynamicWorld->addRigidBody(rigidbody);
	rigidbody->setDamping(0.7f, 0.7f);
	if (isDynamic) {
		rigidbody->setCcdMotionThreshold(0.0000001f);
		rigidbody->setCcdSweptSphereRadius(0.5f);
	}
	return rigidbody;

}
void PhysicsManager::SetWorldGravity(btVector3 gravity) {
	_dynamicWorld->setGravity(gravity);
}

btDynamicsWorld* PhysicsWrapper::PhysicsManager::GetDynamicWorld() {
	return _dynamicWorld;
}

void PhysicsWrapper::PhysicsManager::setContactStartCallback(ContactStartedCallback funtion) {
	gContactStartedCallback = funtion;
}

void PhysicsWrapper::PhysicsManager::setContactProcessCallback(ContactProcessedCallback funtion) {
	gContactProcessedCallback = funtion;
}

void PhysicsWrapper::PhysicsManager::setContactEndedCallback(ContactEndedCallback funtion) {
	gContactEndedCallback = funtion;
}

void PhysicsManager::RemoveRigidBodyFromWorld(btRigidBody* rb) {
	_dynamicWorld->removeRigidBody(rb);
}

void PhysicsManager::Update(float dT) {
	_dynamicWorld->stepSimulation(dT / 1000.f);
}
RaycastInfo PhysicsWrapper::PhysicsManager::createRaycast(LMVector3 from, LMVector3 direction) {
	RaycastInfo newRaycastInfo = RaycastInfo();

	btCollisionWorld::ClosestRayResultCallback rayCallback(LmToBullet(from), LmToBullet(direction));

	PhysicsManager::GetInstance()->GetDynamicWorld()->rayTest(LmToBullet(from), LmToBullet(direction), rayCallback);
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

PhysicsWrapper::RigidBodyInfo::RigidBodyInfo() {
	type = 0;
	boxSize = btVector3();
	sphereSize = 0.f;
	capsuleRadius = 0.f;
	capsuleHeight = 0.f;
	origin = btVector3();
	mass = 0.f;
}

PhysicsWrapper::RaycastInfo::RaycastInfo() {
	hasHit = false;
	hitPos = LMVector3();
	hitVNormal = LMVector3();
}
