#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"
#include "LMVector.h"
//struct LMVector3;
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
namespace OgreWrapper {
	class RenderScene;
	class Node;
}

namespace LocoMotor {
	class Scene;
	class GameObject;

	class MOTOR_API Camera : public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "Camera";
		};
		// Para crear la camara se necesita tanto la escena como la escena de Render
		// 
		Camera();
		
		OgreWrapper::Node* _node;

		void InitComponent() override;
		void Update(float dt) override;

		void SetTarget(GameObject* target, LMVector3 offset);

	private:
		Scene* _scene;
		OgreWrapper::RenderScene* _renderScn;

		GameObject* _target;
		LMVector3 _offset;

		//GetCamera();
	};
}