#pragma once
#ifndef _RIGIDBODY_COMPONENT_H_
#define _RIGIDBODY_COMPONENT_H_
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"
class btRigidBody;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	class BulletRigidBody;
}

enum ActiveState {
	LM_ACTIVE = 1,
	LM_ISLAND_SLEEPING = 2,
	LM_WANTS_DEACTIVATION = 3,
	LM_DISABLE_DEACTIVATION = 4,
	LM_DISABLE_SIMULATION = 5
};

namespace LocoMotor {
	class LMVector3;
	class LMQuaternion;
	class MeshStrider;
	class MOTOR_API RigidBody : public Component {
	public:
		RigidBody();
		/// @brief Constructor
		void Start(float mass);
		/// @brief Destructor
		virtual ~RigidBody();
		/// @brief Add force to the body
		/// @param force to add
		void addForce(LMVector3 force);
		/// @brief 
		void PreStart() override;
		/// @brief 
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void PreUpdate(float dt) override;
		/// @brief Sets the body rotation
		/// @param rot Rotation to set
		void setRotation(LMQuaternion rot);
		/// @brief Sets the body rotation
		/// @param rot Rotation to set
		void setPosition(LMVector3 pos);
		/// @brief Enable/Disable the gravity force affected to this body
		/// @param gravity 
		void useGravity(LMVector3 gravity);
		/// @brief Freeze the position of the rigidbody , limit the motion of position in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezePosition(LMVector3 freezeAxis);
		/// @brief Freeze the rotation of the rigidbody , limit the motion of rotation in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezeRotation(LMVector3 freezeAxis);
		/// @brief Checks if the rigid body component of a game object collides with another
		/// @param other The parameter "other" is a pointer to a GameObject object, which is being checked for
		/// collision with the current object's RigidBodyComponent.
		/// @return Boolean value. It returns true if the rigid body component of the current game object
		/// collides with the rigid body component of the other game object passed as a parameter, and false
		/// otherwise.
		bool checkCollision(GameObject* other);
		/// @brief Returns the rigid body component of a locomotor.
		/// @return a pointer to a btRigidBody object, which is the physics body component of the LocoMotor.
		btRigidBody* getBody();
		/// @brief Convert the body to be a Trigger(No contact Response)
		void beATrigger();
		/// @brief Methods to return RaycastInfo
		/// @param from The starting point of the raycast in 3D space.
		/// @param to The "to" parameter is a 3D vector representing the end point of the raycast. It is the
		/// point in space where the raycast endsand checks for collisions or intersections with objects in the
		/// scene.
		/// @return A boolean value indicating whether a raycast from the "from" point to the "to" point has hit
		/// any objects in the physics simulation.
		bool GetRaycastHit(LMVector3 from, LMVector3 to);
		/// @brief Gets the raycast hit point
		/// @param from The starting point of the raycast, represented as a 3D vector.
		/// @param to The "to" parameter is the end point of the raycast, which is the point in 3D space where
		/// the ray ends or terminates.
		/// @return Returns the point in LmVector3
		LMVector3 GetraycastHitPoint(LMVector3 from, LMVector3 to);
		/// @brief Gets the raycast hit normal
		/// @param from The starting point of the raycast, represented as a 3D vector.
		/// @param to The "to" parameter is the end point of the raycast, which is the point in 3D space where
		/// the ray ends or terminates.
		/// @return Returns the normal in LMVector3
		LMVector3 GethasRaycastHitNormal(LMVector3 from, LMVector3 to);
		/// @brief Set the body to be a group of collision , if not set the group is 0
		/// @param group To set
		void SetCollisionGroup(int group);
		/// @brief Gets the number of rigidbodys group 
		/// @return The number of group
		int GetCollisionGroup();
		/// @brief Set the mask that want to collide , the number is the group you want to collide
		/// @param mask The group number
		void SetCollisionMask(int mask);
		/// @brief Gets actual collision mask
		/// @return the number of collsion mask
		int GetCollisionMask();
		/// @brief Gets the linearvelocity of the body
		/// @return Return a LMVector3 of linear velocity
		LMVector3 GetLinearVelocity();
		/// @brief Sets the linear velocity of the body
		/// @param newAngularVelocity 
		void SetLinearVelocity(LMVector3 newLinearVelocity);
		/// @brief Gets the total torque of the body
		/// @return Return a LMVector3 of total torque
		LMVector3 GetTotalTorque();
		/// @brief Gets the turn velocity of the body
		/// @return Return a LMVector3 of turn velocity
		LMVector3 GetTurnVelocity();
		/// @brief Gets/Sets the angular velocity of the body
		/// @return Return a LMVector3 of turn velocity
		LMVector3 GetAngularVelocity();
		/// @brief Sets the angular velocity of a rigid body component using a given LMVector3 value.
		/// @param newAngularVelocity Variable that represents the new angular velocity to be set for
		/// the rigid body component.
		void SetAngularVelocity(LMVector3 newAngularVelocity);
		/// @brief Applies a torque impulse to the body
		/// @param impulse the impulse to aplly
		void ApplyTorqueImpulse(LMVector3 impulse);
		/// @brief Set the friction of this rigidbody
		/// @param fric the new friction value
		void SetFriction(float fric);
		/// @brief Add the body to detect raycast
		void UseItAsRaycast();
		/// @brief Set the activation state of a body (Should sleep / not)
		void SetActivationState(ActiveState newState);
	private:
		float _mass;
		btRigidBody* _body;
		float _damping;
		float _angDamping;
		bool _gravity;
		MeshStrider* _ms;
		bool _trigger = false;
		int _collisionGroup;
		int _collisionMask;
		bool _raycast = false;
		bool _beATrigger = false;

	};
}

#endif // !_RIGIDBODY_COMPONENT_H

