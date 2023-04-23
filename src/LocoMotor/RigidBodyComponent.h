#pragma once
#ifndef _RIGIDBODY_COMPONENT_H_
#define _RIGIDBODY_COMPONENT_H_
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"
class LMVector3;
class LMQuaternion;
class btRigidBody;
class MeshStrider;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	class BulletRigidBody;
}
namespace LocoMotor {
	class MOTOR_API RigidBodyComponent : public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "RigidBodyComponent";
		};
		RigidBodyComponent();
		/// @brief Constructor
		void Start(float mass);
		/// @brief Destructor
		virtual ~RigidBodyComponent();
		/// @brief Add force to the body
		/// @param force to add
		void addForce(LMVector3 force);
		/// @brief 
		void Start() override;
		/// @brief 
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
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
		/// @brief 
		/// @return 
		bool checkCollision(GameObject* other);
		/// @brief 
		/// @return 
		btRigidBody* getBody();
		/// @brief Convert the body to be a Trigger(No contact Response)
		void beATrigger();
		/// @brief Methods to return RaycastInfo
		bool GetRaycastHit(LMVector3 from, LMVector3 to);
		/// @brief Gets the raycast hit point
		/// @param from Vector
		/// @param to Vector
		/// @return Returns the point in LmVector3
		LMVector3 GetraycastHitPoint(LMVector3 from, LMVector3 to);
		/// @brief Gets the raycast hit normal
		/// @param from Vector
		/// @param to Vector
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
		/// @brief Gets the total torque of the body
		/// @return Return a LMVector3 of total torque
		LMVector3 GetTotalTorque();
		/// @brief Gets the turn velocity of the body
		/// @return Return a LMVector3 of turn velocity
		LMVector3 GetTurnVelocity();
		/// @brief Applies a torque impulse to the body
		/// @param impulse the impulse to aplly
		void ApplyTorqueImpulse(LMVector3 impulse);
		/// @brief Set The friction of this rigidbody
		/// @param fric the new friction value
		void SetFriction(float fric);
	private:
		float _mass;
		btRigidBody* _body;
		float _damping;
		float _angDamping;
		bool _gravity;
		MeshStrider* _ms;
		bool _trigger = false;
		int collisionGroup;
		int collisionMask;

	};
}

#endif // !_RIGIDBODY_COMPONENT_H

