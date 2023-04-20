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
		void InitComponent() override;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void Start() override;
		/// @brief Updates the source's position and velocity in the world
		/// @param dt DeltaTime used to calculate the velocity by comparing last position
		void Update(const float dt) override;

		const LMVector3& GetPosition();
		void SetPosition(const LMVector3& newPosition);

		const LMQuaternion& GetRotation();
		void SetRotation(const LMQuaternion& newRotation);

		const LMVector3& GetSize();
		void SetSize(const LMVector3& newSize);

		//void LookAt(const LMVector3& position, const LMVector3& upward);

		void SetUpwards(const LMVector3& newUpward);
		void SetForward(const LMVector3& newForward);
		void LookAt(const LMVector3& lookPos);
		void LookAt(const LMVector3& lookPos, const LMVector3& up);

	private:

		LMVector3 _position;
		LMVector3 _scale;
		LMQuaternion _direction;

		void SetLocalPosition(const LMVector3& newPosition);
		void SetLocalRotation(const LMQuaternion& newRotation);
		void SetLocalScale(const LMVector3& newSize);

		void SetPhysPosition(const LMVector3& newPosition);
		void SetPhysRotation(const LMQuaternion& newRotation);
		void SetPhysScale(const LMVector3& newsize);
		


		OgreWrapper::Node* _gObjNode;

	};
}

#endif // !LM_TRANSFORM
