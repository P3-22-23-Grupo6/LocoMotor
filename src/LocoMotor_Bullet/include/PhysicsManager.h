#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#pragma once
#include <vector>
#include <btBulletDynamicsCommon.h>
#include "Singleton.h"
namespace PhysicsWrapper {
	/// <summary>
	/// Info to create a RigidBody
	/// </summary>
	/// <param name="Type"> The type of the rigidbody, could be box or sphere </param>
	/// <param name="boxSize"> The size of the box if Type is Box </param>
	/// <param name="size"> The size of the sphere if Type is Sphere </param>
	/// <param name="Origin"> The origin point of transform </param>
	/// <param name="mass"> The mass of rigidbody, if mass !=0 , it is dynamic </param>
	struct RigidBodyInfo {
		btVector3 boxSize;
		float size;
		btVector3 origin;
		float mass;
	};
	class BulletRigidBody;
	class PhysicsManager : public Singleton<PhysicsWrapper::PhysicsManager> {
		friend Singleton<PhysicsWrapper::PhysicsManager>;
	public:

		/// <summary>
		/// Update the physics world , steps the physic simulation
		/// </summary>
		void Update();
		/// <summary>
		/// Create the rigidBody with the info given
		/// </summary>
		/// <param name="info"> The information to build the rigidBody </param>
		/// <returns>The BulletRigidBody pointer created</returns>
		BulletRigidBody* CreateRigidBody(RigidBodyInfo info);
		/// <summary>
		/// Add the RigidBody to the physics world
		/// </summary>
		/// <param name="rb"> The pointer of the rigidbody </param>
		void AddRigidBodyToWorld(btRigidBody* rb);
		/// <summary>
		/// Add the RigidBody to the physics world
		/// </summary>
		/// <param name="rb"> The pointer of the rigidbody </param>
		void RemoveRigidBodyFromWorld(btRigidBody* rb);
		/// <summary>
		/// Sets the worlds gravity
		/// </summary>
		/// <param name="gravity"> The Vector3 gravity you want to set </param>
		void SetWorldGravity(btVector3 gravity);

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
