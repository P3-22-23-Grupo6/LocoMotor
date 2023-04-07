#pragma once
#ifndef _RIGIDBODY_COMPONENT_H_
#define _RIGIDBODY_COMPONENT_H_
#include "Component.h"
class LMVector3;
class LMQuaternion;
class BulletRigidBody;
class MeshStrider;
namespace PhysicsWrapper {
	class RigidBodyInfo;
	class BulletRigidBody;
}
namespace LocoMotor {
	class RigidBodyComponent : public Component {
	public:
		const static std::string name;
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
		/// @brief Set the bodys mass (NOT WORKING)
		void setMass(float m);
		/// @brief Enable/Disable the gravity force affected to this body
		/// @param gravity 
		void useGravity(bool gravity);
		/// @brief Freeze the position of the rigidbody , limit the motion of position in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezePosition(LMVector3 freezeAxis);
		/// @brief Freeze the rotation of the rigidbody , limit the motion of rotation in those axis
		/// @param axis LMVector3 x,y,z axis , 0 means limit(stop motion) , 1 means no limit(allow motion)
		void FreezeRotation(LMVector3 freezeAxis);
		/// @brief Set the body to Dynamic state
		void setDynamic();
		/// @brief Set the body to Kinematic state
		void setKinematic();
		/// @brief Set the body to Static state
		void setStatic();
		/// @brief Set the body to no contact response state / trigger
		void setNoContactResponse();
		/// @brief 
		/// @return 
		bool checkCollision(GameObject* go);
		/// @brief 
		/// @return 
		PhysicsWrapper::BulletRigidBody* getBody();
		/// @brief Methods to return RaycastInfo
		bool GetRaycastHit(LMVector3 from, LMVector3 to);
		LMVector3 GetraycastHitPoint(LMVector3 from, LMVector3 to);
		LMVector3 GethasRaycastHitNormal(LMVector3 from, LMVector3 to);
	private:
		float _mass;
		PhysicsWrapper::BulletRigidBody* _body;
		float _damping;
		float _angDamping;
		bool _gravity;
		MeshStrider* _ms;

	};
}

#endif // !_RIGIDBODY_COMPONENT_H

