#pragma once
#ifndef _RIGIDBODY_COMPONENT_H_
#define _RIGIDBODY_COMPONENT_H_
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
	class RigidBodyComponent : public Component {
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
		LMVector3 GetraycastHitPoint(LMVector3 from, LMVector3 to);
		LMVector3 GethasRaycastHitNormal(LMVector3 from, LMVector3 to);

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

	};
}

#endif // !_RIGIDBODY_COMPONENT_H

