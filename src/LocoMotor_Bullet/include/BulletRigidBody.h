#pragma once
#ifndef _BULLETRIGIDBODY_H_
#define _BULLETRIGIDBODY_H_

class btRigidBody;
class btCollisionShape;
class LMQuaternion;
class LMVector3;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	class BulletRigidBody {
	public:
		/// @brief Constructor by rigidBodyInfo to create BulletRigidBody
		/// @param info RigidBodyInfo The info of the rigidBody 
		BulletRigidBody(RigidBodyInfo info);
		/// @brief Add central force to the rigidBody
		/// @param force LMVector3 The force that is applied
		void AddForce(LMVector3 force);
		/// @brief Set the rotation of rigidBody
		/// @param rot LMQuaternion Rotation to apply
		void setRotation(LMQuaternion rot);
		/// @brief Get the rotation of rigidBody
		/// @return LMQuaternion Actual rotation of rigidBody
		LMQuaternion getRotation();
		/// @brief Set the gravity force affected to this rigidBody
		/// @param gravity LMVector3 The gravity force
		void setGravity(LMVector3 gravity);
		/// @brief Freeze the position of the rigidbody , limit the motion of position in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezePosition(LMVector3 axis);
		/// @brief Freeze the rotation of the rigidbody , limit the motion of rotation in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezeRotation(LMVector3 axis);
		/// @brief Sets the rigidbodys mass
		/// @param m The mass to set
		void setMass(float m);
		/// @brief set the rigidBodyState (dynamic,kinematic,static)
		/// @param state int The state you want to set to the rigidBody, 0=Dynamic, 1=Static, 2=Kinematic
		void setBodystate(int state);
		/// @brief Destructor of BulletRigidBody
		~BulletRigidBody();
	private:
		btRigidBody* _rigidBody = nullptr;
		btCollisionShape* _shape = nullptr;
	};
}


#endif