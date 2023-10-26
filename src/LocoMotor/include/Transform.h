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
		void InitRuntime(LMVector3 initPos = LMVector3(0, 0, 0), LMVector3 initRot = LMVector3(0, 0, 0), LMVector3 initScale = LMVector3(1, 1, 1));
		void Start() override;
		/// @brief Updates the source's position and velocity in the world
		/// @param dt DeltaTime used to calculate the velocity by comparing last position
		void Update(const float dt) override;
		/// @brief  Returns the World position of the LocoMotor object.
		/// @return vector
		const LMVector3& GetPosition();
		/// @brief  Returns the World position of the LocoMotor object.
		/// @return vector
		const LMVector3& GetLocalPosition();
		/// @brief Sets the world position of the LocoMotor object.
		/// @param newPosition The new position 
		void SetPosition(const LMVector3& newPosition);
		/// @brief Sets the local position of the LocoMotor object.
		/// @param newLocalPosition The new local position 
		void SetLocalPosition(const LMVector3& newLocalPosition);

		/// @brief Returns the rotation of the LocoMotor object.
		/// @return quaterinion
		const LMQuaternion& GetRotation();
		/// @brief Returns the Rotation in Euler Degrees of the LocoMotor object.
		/// @return vector 
		const LMVector3& GetEulerRotation();
		/// @brief Returns the rotation of the LocoMotor object.
		/// @return quaterinion
		const LMQuaternion& GetLocalRotation();
		/// @brief Returns the local position of the LocoMotor object.
		/// @return vector 
		const LMVector3& GetLocalEulerRotation();

		/// @brief Sets the rotation of the LocoMotor object.
		/// @param newRotation The new rotation
		void SetRotation(const LMQuaternion& newRotation);
		void SetRotation(const LMVector3& newRotation);
		/// @brief Sets the local rotation of the LocoMotor object (for children)
		/// @param newRotation The new rotation of the child 
		void SetLocalRotation(const LMQuaternion& newRotation);
		void SetLocalRotation(const LMVector3& newRotation);
		
		/// @brief Returns the size of the LocoMotor object.
		/// @return vector
		const LMVector3& GetSize();
		/// @brief Sets the size of the LocoMotor object.
		/// @param newSize The new size
		void SetSize(const LMVector3& newSize);
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
		void AddBillboard(const LMVector3& billPos, const std::string billMat, const std::string billName);

		//CHILDREN
		
		std::vector<Transform*> childList;
		/// @brief Adds a Transform as a child; it will inherit t/r/s from this transform
		/// @param trToAdd transform to add as a child
		/// @param resetLocal to set the child position same as parent(local = 0,0,0); false by default
		void AddChild(Transform* trToAdd, bool resetLocal = false);
		/// @brief Removes a child Transform
		void RemoveChild(Transform* trToRemove);
		//Sets a transform as a parent of this Transform
		void SetParent(Transform* trParent);
		const Transform* GetParent();

	private:

		LMVector3 _position;
		LMVector3 _localPosition;
		LMVector3 _scale;
		LMVector3 _localScale;
		LMQuaternion _direction;
		LMQuaternion _localDirection;
		Transform* parent;

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
