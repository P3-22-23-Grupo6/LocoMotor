#pragma once
#ifndef LM_TRANSFORM
#define LM_TRANSFORM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"
#include "LMVector.h"

namespace OgreWrapper {
	class Node;
}

namespace LocoMotor {
	class MOTOR_API Transform : public Component {

	public:

		Transform();
		~Transform();
		/// @brief Initializes a component for a game object and registers its transform.
		void InitComponent() override;
		/// @brief Initializes the position, rotation, and scale of a game object's transform based on input parameters.
		/// @param params A vector of pairs, where each pair contains a string representing a parameter nameand
		/// a string representing the value of that parameter.The function uses these parameters to initialize
		/// the position, rotation, and scale of a transform component.
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void Start() override;
		/// @brief Updates the source's position and velocity in the world
		/// @param dt DeltaTime used to calculate the velocity by comparing last position
		void Update(const float dt) override;
		/// @brief  Returns the local position of the LocoMotor object.
		/// @return vector
		const LMVector3& GetPosition();
		/// @brief Sets the position of the LocoMotor object.
		/// @param newPosition The new position 
		void SetPosition(const LMVector3& newPosition);
		/// @brief Returns the rotation of the LocoMotor object.
		/// @return quaterinion
		const LMQuaternion& GetRotation();
		/// @brief Sets the rotation of the LocoMotor object.
		/// @param newRotation The new rotation
		void SetRotation(const LMQuaternion& newRotation);
		/// @brief Returns the position of the LocoMotor object.
		/// @return vector 
		const LMVector3& GetEulerRotation();
		/// @brief Sets the rotation of the LocoMotor object.
		/// @param newRotation The new vector
		void SetEulerRotation(const LMVector3& newRotation);
		/// @brief Returns the size of the LocoMotor object.
		/// @return vector
		const LMVector3& GetSize();
		/// @brief Sets the size of the LocoMotor object.
		/// @param newSize The new size
		void SetSize(const LMVector3& newSize);

		//void LookAt(const LMVector3& position, const LMVector3& upward);

		/// @brief Sets up a new upward direction for a LocoMotor object by calculating the rotation
		/// needed to align the current upward direction with the new one.
		/// @param newUpward A LMVector3 representing the new upward direction to set for the LocoMotor object.
		void SetUpwards(const LMVector3& newUpward);
		/// @brief Sets the forward direction of a LocoMotor object by calculating the rotation needed to
		/// align the current forward direction with a new given direction.
		/// @param newForward  A LMVector3 representing the new forward direction that the LocoMotor should face.
		void SetForward(const LMVector3& newForward);
		/// @brief Updates the forward vector of a LocoMotor object.
		/// @param lookPos A LMVector3 representing the position to look at.
		void LookAt(const LMVector3& lookPos);
		/// @brief Sets the forward and upward vectors of a transform to look at a specified position with
		/// a specified upward direction.
		/// @param lookPos A LMVector3 representing the position that the LocoMotor's Transform should be
		/// looking at.
		/// @param up The "up" parameter is a LMVector3 that represents the direction that is considered "up" in
		/// the world space.This is used to ensure that the object being transformed maintains a consistent
		/// orientation, even if it is rotated.
		void LookAt(const LMVector3& lookPos, const LMVector3& up);

	private:

		LMVector3 _position;
		LMVector3 _scale;
		LMVector3 _directionEuler;
		LMQuaternion _direction;

		/// @brief Sets the local position of a transform.
		/// @param newPosition newPosition is a constant reference to an LMVector3 object, which represents the
		/// new local position that we want to set for the LocoMotor object.
		void SetLocalPosition(const LMVector3& newPosition);
		/// @brief Sets the local rotation of a LocoMotor object.
		/// @param newRotation A LMQuaternion object representing the new rotation to be set for the LocoMotor's
		/// Transform.
		void SetLocalRotation(const LMQuaternion& newRotation);
		/// @brief Sets the local Euler rotation of a LocoMotor object.
		/// @param newRotation A LMVector3 object representing the new rotation to be set in local Euler angles. 
		void SetLocalEulerRotation(const LMVector3& newRotation);
		/// @brief Sets the local scale of a transform.
		/// @param newSize Is a reference to an LMVector3 object, which represents the new scale of the
		/// object.It contains three float values representing the new scale along the x, y, and z axes.
		void SetLocalScale(const LMVector3& newSize);
		/// @brief Sets the physical position of a game object with a rigid body component.
		/// @param newPosition  A constant reference to an LMVector3 object representing the new physical
		/// position to set for the LocoMotor object.
		void SetPhysPosition(const LMVector3& newPosition);
		/// @brief Sets the physical rotation of a game object with a rigid body component.
		/// @param newRotation The new rotation that the function is setting for the physics object. It is of
		/// type LMQuaternion, which is likely a custom quaternion class specific to the game engine or
		/// framework being used.
		void SetPhysRotation(const LMQuaternion& newRotation);
		/// @brief Sets the physical Euler rotation of a game object's rigid body component.
		/// @param newRotation A LMVector3 object representing the new rotation to be set for the Transform.
		void SetPhysEulerRotation(const LMVector3& newRotation);
		/// @brief 
		/// @param newsize 
		void SetPhysScale(const LMVector3& newsize);



		OgreWrapper::Node* _gObjNode;

	};
}

#endif // !LM_TRANSFORM
