#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_
#pragma once
#include <vector>
//#include <btBulletDynamicsCommon.h>
#include "lmVector.h"
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btRigidBody;
namespace BulletWrapper {

	/// <summary>
	/// Info to create a RigidBody
	/// </summary>
	/// <param name="Type"> The type of the rigidbody, could be box or sphere </param>
	/// <param name="boxSize"> The size of the box if Type is Box </param>
	/// <param name="size"> The size of the sphere if Type is Sphere </param>
	/// <param name="Origin"> The origin point of transform </param>
	/// <param name="mass"> The mass of rigidbody, if mass !=0 , it is dynamic </param>
	struct RigidBodyInfo {
		LMVector3 boxSize;
		float size;
		LMVector3 origin;
		float mass;
	};
	class BulletRigidBody;
	class BulletManager {
	public:

		/// <summary>
		/// Update the physics world , steps the physic simulation
		/// </summary>
		void Update ();
		/// <summary>
		/// A method to get the <c>BulletManager</c> singleton instance.
		/// <c>BulletManager::InitBullet</c> must be called before any calls to <c>BulletManager::getInstance</c> or
		/// else it will return nullptr.
		/// </summary>
		/// <returns>The <c>BulletManager</c> singleton instance if init has been called beforehand. Returns <c>nullptr</c> if not</returns>
		static BulletManager* GetInstance ();
		/// <summary>
		/// Create the rigidBody with the info given
		/// </summary>
		/// <param name="info"> The information to build the rigidBody </param>
		void CreateRigidBody (RigidBodyInfo info);
		/// <summary>
		/// Add the RigidBody to the physics world
		/// </summary>
		/// <param name="rb"> The pointer of the rigidbody </param>
		void AddRigidBodyToWorld (btRigidBody* rb);
		/// <summary>
		/// Add the RigidBody to the physics world
		/// </summary>
		/// <param name="rb"> The pointer of the rigidbody </param>
		void RemoveRigidBodyFromWorld (btRigidBody* rb);
		/// <summary>
		/// Initializes the <c>BulletManager</c> singleton instance.
		/// This method must be called before any calls to <c>BulletManager::getInstance</c>.
		/// </summary>
		/// <returns>void</returns>
		static void InitBullet ();
		/// <summary>
		/// Sets the worlds gravity
		/// </summary>
		/// <param name="gravity"> The Vector3 gravity you want to set </param>
		void SetWorldGravity (btVector3 gravity);

	private:
		//La instacia del Manager
		static BulletManager* _instance;
		//Configuraciones para crear el mundo físico
		btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
		btCollisionDispatcher* _dispatcher = nullptr;
		btBroadphaseInterface* _overlappingPairCache = nullptr;
		btSequentialImpulseConstraintSolver* _solver = nullptr;
		btDynamicsWorld* _dynamicWorld = nullptr;
		//Constructora y destructora de la clase
		std::vector<BulletRigidBody*> _vRigidBody;
		BulletManager ();
		~BulletManager ();

	};
}
#endif 
