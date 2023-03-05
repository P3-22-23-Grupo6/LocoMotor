#pragma once
#ifndef _BULLETRIGIDBODY_H_
#define _BULLETRIGIDBODY_H_

class btRigidBody;
class btCollisionShape;
class LMQuaternion;
class LMVector3;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	//class BulletManager;
	class BulletRigidBody {
	public:
		/// @brief Constructor by rigidBodyInfo to create BulletRigidBody
		/// @param info RigidBodyInfo The info of the rigidBody 
		BulletRigidBody(RigidBodyInfo info);
		/// @brief Destructor of BulletRigidBody
		~BulletRigidBody();
		/// @brief Add central force to the rigidBody
		/// @param force LMVector3 The force that is applied
		void AddForce(LMVector3 force);
		/// @brief Set the rotation of rigidBody
		/// @param rot LMQuaternion Rotation to apply
		void setRotation(LMQuaternion rot);
		/// @brief Get the rotation of rigidBody
		/// @return LMQuaternion Actual rotation of rigidBody
		LMQuaternion getRotation();
	private:
		btRigidBody* _rigidBody = nullptr;
		btCollisionShape* _shape = nullptr;
	};
}


#endif