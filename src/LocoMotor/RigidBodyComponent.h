#pragma once
#ifndef _RIGIDBODY_COMPONENT_H_
#define _RIGIDBODY_COMPONENT_H_
#include "Component.h"
class LMVector3;
class BulletRigidBody;
namespace PhysicsWrapper {
	class RigidBodyInfo;
	class BulletRigidBody;
}
namespace LocoMotor {
	class RigidBodyComponent : public LocoMotor::Component {
	public:
		/// @brief Constructor
		RigidBodyComponent(PhysicsWrapper::RigidBodyInfo info);
		/// @brief Destructor
		virtual ~RigidBodyComponent();
		/// @brief Set the bodys mass
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
	private:
		float _mass;
		PhysicsWrapper::BulletRigidBody* _body;
		float _damping;
		float _angDamping;
		bool _gravity;

	};
}

#endif // !_RIGIDBODY_COMPONENT_H

