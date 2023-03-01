#include "BulletManager.h"
#include <iostream>
#include "BulletRigidBody.h"
#include <btBulletDynamicsCommon.h>
using namespace BulletWrapper;
BulletWrapper::BulletManager* Singleton<BulletWrapper::BulletManager>::_instance = nullptr;

BulletWrapper::BulletManager::BulletManager () {

	//Set default configuration
	_collisionConfiguration = new btDefaultCollisionConfiguration ();
	_dispatcher = new btCollisionDispatcher (_collisionConfiguration);
	_overlappingPairCache = new btDbvtBroadphase ();
	_solver = new btSequentialImpulseConstraintSolver;
	//Create Dynamic world
	_dynamicWorld = new btDiscreteDynamicsWorld (_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
	//Set default gravity
	_dynamicWorld->setGravity (btVector3 (0, -10, 0));
}

BulletWrapper::BulletManager::~BulletManager () {
	for (auto rb : _vRigidBody)delete rb;
	_vRigidBody.clear ();
	delete _collisionConfiguration;
	delete _dispatcher;
	delete _overlappingPairCache;
	delete _solver;
	delete _dynamicWorld;
}

//void BulletWrapper::BulletManager::InitBullet () {
//	if (_instance == nullptr) _instance = new BulletManager ();
//}

//BulletWrapper::BulletManager* BulletWrapper::BulletManager::GetInstance () {
//	if (_instance != nullptr) return _instance;
//	std::cerr << "Debes inicializar con BulletManager::InitBullet() antes de llamar a BulletManager::getInstance()!!\n";
//	return nullptr;
//}
void BulletWrapper::BulletManager::CreateRigidBody (RigidBodyInfo info) {
	BulletRigidBody* brg = new BulletRigidBody (info);
	_vRigidBody.push_back (brg);

}
void BulletWrapper::BulletManager::SetWorldGravity (btVector3 gravity) {
	_dynamicWorld->setGravity (gravity);
}

void BulletWrapper::BulletManager::AddRigidBodyToWorld (btRigidBody* rb) {
	_dynamicWorld->addRigidBody (rb);
}

void BulletWrapper::BulletManager::RemoveRigidBodyFromWorld (btRigidBody* rb) {
	_dynamicWorld->removeRigidBody (rb);
}

void BulletWrapper::BulletManager::Update () {
	_dynamicWorld->stepSimulation (1.0 / 60.0);

	//print positions of all objects
	for (int j = _dynamicWorld->getNumCollisionObjects () - 1; j >= 0; j--) {
		btCollisionObject* obj = _dynamicWorld->getCollisionObjectArray ()[j];
		btRigidBody* body = btRigidBody::upcast (obj);
		btTransform trans;
		if (body && body->getMotionState ()) {
			body->getMotionState ()->getWorldTransform (trans);
		}
		else {
			trans = obj->getWorldTransform ();
		}
		printf ("world pos object %d = %f,%f,%f\n", j, float (trans.getOrigin ().getX ()), float (trans.getOrigin ().getY ()), float (trans.getOrigin ().getZ ()));
	}
}
