#include "PhysicsManager.h"
#include <iostream>
#include "BulletRigidBody.h"
#include <btBulletDynamicsCommon.h>
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
	_dynamicWorld->setGravity(btVector3(0, -9.8, 0));
}

PhysicsManager::~PhysicsManager() {
	for (auto rb : _vRigidBody)delete rb;
	_vRigidBody.clear();
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _overlappingPairCache;
	delete _solver;
	delete _dynamicWorld;
}

BulletRigidBody* PhysicsManager::CreateRigidBody(RigidBodyInfo info) {
	BulletRigidBody* brg = new BulletRigidBody(info);
	_vRigidBody.push_back(brg);
	return brg;

}
void PhysicsManager::SetWorldGravity(btVector3 gravity) {
	_dynamicWorld->setGravity(gravity);
}

void PhysicsManager::AddRigidBodyToWorld(btRigidBody* rb) {
	_dynamicWorld->addRigidBody(rb);
}

void PhysicsManager::RemoveRigidBodyFromWorld(btRigidBody* rb) {
	_dynamicWorld->removeRigidBody(rb);
}

void PhysicsManager::Update() {
	_dynamicWorld->stepSimulation(1.0 / 60.0);

	//print positions of all objects
	for (int j = _dynamicWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
		btCollisionObject* obj = _dynamicWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState()) {
			body->getMotionState()->getWorldTransform(trans);
		}
		else {
			trans = obj->getWorldTransform();
		}
		//trans.setRotation(btQuaternion(1, 1, 1, 1));
		printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		//printf("world rot object %d = %f,%f,%f,%f\n", j, float(trans.getRotation().x()), float(trans.getRotation().y()), float(trans.getRotation().z()), float(trans.getRotation().w()));
		//std::cout<<body->getCollisionFlags();
	}
}
