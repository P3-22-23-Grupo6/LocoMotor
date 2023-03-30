#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#pragma once
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "Singleton.h"
namespace PhysicsWrapper {
	/// @brief Info to create a RigidBody
	/// @param btVector3 boxSize The size of the box if is Box
	/// @param float size The size of the sphere if is Sphere
	/// @param btVector3 origin The origin point of transform
	/// @param float mass The mass of rigidbody, if mass !=0 , it is dynamic
	struct RigidBodyInfo {
		btVector3 boxSize;
		float size;
		btVector3 origin;
		float mass;
	};
	/// @brief Info to retreieve from a Raycast
	/// @param hasHit tells if there was a Collision
	/// @param hitPos The position of the surface hit
	/// @param hitVNormal The normal vector of the surface hit
	struct RaycastInfo {
		bool hasHit;
		btVector3 hitPos;
		btVector3 hitVNormal;
	};

	class BulletRigidBody;
	class PhysicsManager : public Singleton<PhysicsWrapper::PhysicsManager> {
		friend Singleton<PhysicsWrapper::PhysicsManager>;
	public:
		/// @brief Update the physics world , steps the physic simulation
		void Update();
		/// @brief Create the rigidBody with the info given
		/// @param info The information to build the rigidBody
		/// @return The BulletRigidBody pointer created
		BulletRigidBody* CreateRigidBody(RigidBodyInfo info);
		/// @brief Add the RigidBody to the physics world
		/// @param rb The pointer of the rigidbody
		void AddRigidBodyToWorld(btRigidBody* rb);
		/// @brief Add the RigidBody to the physics world
		/// @param rb The pointer of the rigidbody
		void RemoveRigidBodyFromWorld(btRigidBody* rb);
		/// @brief Sets the worlds gravity
		/// @param gravity The Vector3 gravity you want to set
		void SetWorldGravity(btVector3 gravity);
		/// @brief Gets dynamic World
		btDynamicsWorld* GetDynamicWorld();

	private:
		//Configuraciones para crear el mundo físico
		btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
		btCollisionDispatcher* _dispatcher = nullptr;
		btBroadphaseInterface* _overlappingPairCache = nullptr;
		btSequentialImpulseConstraintSolver* _solver = nullptr;
		btDynamicsWorld* _dynamicWorld = nullptr;
		//Constructora y destructora de la clase
		PhysicsManager();
		~PhysicsManager();
		//Vector para guardar los rigidbodys creados
		std::vector<BulletRigidBody*> _vRigidBody;

	};
}
#endif 
