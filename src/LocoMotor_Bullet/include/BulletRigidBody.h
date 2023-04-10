#pragma once
#ifndef _BULLETRIGIDBODY_H_
#define _BULLETRIGIDBODY_H_

class btRigidBody;
class btCollisionShape;
class LMQuaternion;
class LMVector3;
class MeshStrider;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	struct RaycastInfo;
	class BulletRigidBody {
	public:
		/// @brief Constructor by rigidBodyInfo to create BulletRigidBody
		/// @param info RigidBodyInfo The info of the rigidBody 
		BulletRigidBody(RigidBodyInfo info,MeshStrider *mesh=nullptr);
		/// @brief Gets the rigidBodyPosition
		/// @return LMVector3 position
		LMVector3 getPosition();
		/// @brief Check if this body has collision with other body
		/// @param other BulletRigidBody
		/// @return bool true if collides 
		bool checkCollision(BulletRigidBody* other);
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
		/// @brief Reset the box shape size
		/// @param size Vector3 size to reset
		void resetBoxShapeSize(LMVector3 size);
		/// @brief Reset the sphere shape size
		/// @param size float size to reset
		void resetSphereShapeSize(float size);
		/// @brief set the rigidBodyState (dynamic,kinematic,static)
		/// @param state int The state you want to set to the rigidBody, 0=Dynamic, 1=Static, 2=Kinematic
		void setBodystate(int state);
		/// @brief Clear the body force
		void clearForce();
		/// @brief Creates a Raycast
		/// @param the vector from where the raycast is created, and its direction
		RaycastInfo createRaycast(LMVector3 from, LMVector3 direction);
		/// @brief Destructor of BulletRigidBody
		~BulletRigidBody();
	private:
		/// @brief Gets the btRigidBody.
		/// @return btRigidBody
		btRigidBody* getBody();
		btRigidBody* _rigidBody = nullptr;
		btCollisionShape* _shape = nullptr;
	};
}


#endif