#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#pragma once
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "Singleton.h"
#include "LMVector.h"

namespace LocoMotor {
	class MeshStrider;
}
namespace PhysicsWrapper {
	/// @brief Info to create a RigidBody
	/// @param type 1=BoxShape, 2=SphereShape, 3=CapsuleShapeZ
	/// @param btVector3 boxSize The size of the box if is Box
	/// @param float size The size of the sphere if is Sphere
	/// @param capsuleRadius if is capsule
	/// @param capsuleHeight if is capsule
	/// @param btVector3 origin The origin point of transform
	/// @param float mass The mass of rigidbody, if mass !=0 , it is dynamic
	struct RigidBodyInfo {
		int type;
		btVector3 boxSize;
		float sphereSize;
		float capsuleRadius;
		float capsuleHeight;
		btVector3 origin;
		float mass;
		RigidBodyInfo();
	};
	/// @brief Info to retreieve from a Raycast
	/// @param hasHit tells if there was a Collision
	/// @param hitPos The position of the surface hit
	/// @param hitVNormal The normal vector of the surface hit
	struct RaycastInfo {
		bool hasHit;
		LocoMotor::LMVector3 hitPos;
		LocoMotor::LMVector3 hitVNormal;
		RaycastInfo();
	};

	class PhysicsManager : public LocoMotor::Singleton<PhysicsWrapper::PhysicsManager> {
		friend LocoMotor::Singleton<PhysicsWrapper::PhysicsManager>;
	public:
		/// @brief Update the physics world , steps the physic simulation
		void Update(float dT);
		/// @brief Create the rigidBody with the info given
		/// @param info The information to build the rigidBody
		/// @return The BulletRigidBody pointer created
		btRigidBody* CreateRigidBody(RigidBodyInfo info, LocoMotor::MeshStrider* ms = nullptr);
		/// @brief Add the RigidBody to the physics world
		/// @param rb The pointer of the rigidbody
		void RemoveRigidBodyFromWorld(btRigidBody* rb);
		/// @brief Sets the worlds gravity
		/// @param gravity The Vector3 gravity you want to set
		void SetWorldGravity(btVector3 gravity);
		/// @brief Gets dynamic World
		btDynamicsWorld* GetDynamicWorld();
		/// @brief Sets the callback when two body starts contact
		void SetContactStartCallback(ContactStartedCallback funtion);
		/// @brief Sets the callback when two body is in contact
		void SetContactProcessCallback(ContactProcessedCallback funtion);
		/// @brief Sets the callback when two body ends contact
		void SetContactEndedCallback(ContactEndedCallback funtion);
		/// @brief Creates a raycast from point to a direction
		/// @param from The start point of raycast
		/// @param direction The direction to raycast
		/// @return The information of the raycast
		RaycastInfo CreateRaycast(LocoMotor::LMVector3 from, LocoMotor::LMVector3 direction);

	private:
		//Configuration to create the physic world
		btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
		btCollisionDispatcher* _dispatcher = nullptr;
		btBroadphaseInterface* _overlappingPairCache = nullptr;
		btSequentialImpulseConstraintSolver* _solver = nullptr;
		btDynamicsWorld* _dynamicWorld = nullptr;
		PhysicsManager();
		~PhysicsManager();
	};
}
#endif 
