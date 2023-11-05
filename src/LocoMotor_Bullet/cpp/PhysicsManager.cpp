#include "PhysicsManager.h"
#include "MeshStrider.h"
#include "LmVectorConverter.h"
#include "RaycastCallBack.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <btBulletCollisionCommon.h>
#include <LinearMath/btVector3.h>
#include <BulletCollision/CollisionShapes/btTriangleShape.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>

using namespace PhysicsWrapper;
using namespace LocoMotor;
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
	_dynamicWorld->setGravity(btVector3(0, -9.8f, 0));
	//btIDebugDraw* a;
	//a->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	//_dynamicWorld->setDebugDrawer(a);
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
	btCollisionShape* shape = nullptr;
	if (ms != nullptr) {
		shape = new btBvhTriangleMeshShape(ms, true, true);
	}
	else {
		if (info.capsuleHeight > 0.0)
			shape = new btCapsuleShapeZ(info.capsuleRadius, info.capsuleHeight);
		else if (info.sphereSize <= 0.0)
			shape = new btBoxShape(info.boxSize);
		else if (info.sphereSize)
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
		rigidbody->setCcdMotionThreshold(0.000000001f);//0.0000001f
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

void PhysicsWrapper::PhysicsManager::SetContactStartCallback(ContactStartedCallback funtion) {
	gContactStartedCallback = funtion;
}

void PhysicsWrapper::PhysicsManager::SetContactProcessCallback(ContactProcessedCallback funtion) {
	gContactProcessedCallback = funtion;
}

void PhysicsWrapper::PhysicsManager::SetContactEndedCallback(ContactEndedCallback funtion) {
	gContactEndedCallback = funtion;
}

void PhysicsManager::RemoveRigidBodyFromWorld(btRigidBody* rb) {
	_dynamicWorld->removeRigidBody(rb);
}

void PhysicsManager::Update(float dT) {
	_dynamicWorld->stepSimulation(dT / 1000.f, 60);
}

RaycastInfo PhysicsWrapper::PhysicsManager::CreateRaycast(LMVector3 from, LMVector3 direction) {
	RaycastInfo newRaycastInfo = RaycastInfo();

	ClosestRayCallbackBullet rayCallback(LmToBullet(from), LmToBullet(direction));
	newRaycastInfo.hitObject = (btRigidBody*) rayCallback.m_collisionObject;
	newRaycastInfo.hitObject = (btRigidBody*) rayCallback.m_collisionObject;
	PhysicsManager::GetInstance()->GetDynamicWorld()->rayTest(LmToBullet(from), LmToBullet(direction), rayCallback);
	if (rayCallback.hasHit()) {
		newRaycastInfo.hasHit = true;
		newRaycastInfo.hitPos = LMVector3(rayCallback.m_hitPointWorld.getX(),
										  rayCallback.m_hitPointWorld.getY(),
										  rayCallback.m_hitPointWorld.getZ());
		newRaycastInfo.hitVNormal = LMVector3(rayCallback.m_hitNormalWorld.getX(),
											  rayCallback.m_hitNormalWorld.getY(),
											  rayCallback.m_hitNormalWorld.getZ());
		/*if (newRaycastInfo.hitObject) {
			if (newRaycastInfo.hitObject->getCollisionShape()->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE)
			{
				btTriangleShape* triangleShape = static_cast<btTriangleShape*>(newRaycastInfo.hitObject->getCollisionShape());
				// Get the triangle's vertices

				btVector3 vertex0 = triangleShape->m_vertices1[newRaycastInfo.m_localShapeInfo.m_triangleIndex[0]];
				btVector3 vertex1 = triangleShape->m_vertices1[newRaycastInfo.m_localShapeInfo.m_triangleIndex[1]];
				btVector3 vertex2 = triangleShape->m_vertices1[newRaycastInfo.m_localShapeInfo.m_triangleIndex[2]];

				// Now, you can use vertex0, vertex1, and vertex2 as the vertices of the hit triangle.
			}

		}*/
	}
		else newRaycastInfo.hasHit = false;
		return newRaycastInfo;
}
LocoMotor::LMVector3 PhysicsWrapper::PhysicsManager::CalculateBarycentricCoordinates(RaycastInfo rayInf)
{
	btVector3 vertex1;
	btVector3 vertex2;
	btVector3 vertex3;
	btVector3 point;
	btCollisionShape* colShape = rayInf.hitObject->getCollisionShape();

	// Calculate the vectors from vertex1 to the other vertices
	btVector3 v0 = vertex2 - vertex1;
	btVector3 v1 = vertex3 - vertex1;
	btVector3 v2 = point - vertex1;

	// Calculate dot products
	double dot00 = v0.dot(v0);
	double dot01 = v0.dot(v1);
	double dot02 = v0.dot(v2);
	double dot11 = v1.dot(v1);
	double dot12 = v1.dot(v2);

	// Compute barycentric coordinates
	double inv_denom = 1.0 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
	double v = (dot00 * dot12 - dot01 * dot02) * inv_denom;
	double w = 1.0 - u - v;
	LMVector3 returnVect = BulletToLm(btVector3(u, v, w));
	return returnVect;
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
