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
	class Camera;
	class RenderScene;
	class Node;
}

namespace LocoMotor {
	class Scene;
	class GameObject;

	class MOTOR_API Camera : public Component {
	public:
		// Para crear la camara se necesita tanto la escena como la escena de Render
		// 
		Camera();
		
		OgreWrapper::Node* _node;

		void InitComponent() override;
		void Update(float dt) override;

		void SetTarget(GameObject* target, LMVector3 offset);
		//Metodo de Ogre para Trackear una entidad(player)
		void SetTracking(bool isTracking, GameObject* target, LMVector3 offset);
		void SetFOV(float newFov);

	private:
		OgreWrapper::Camera* cam;
		Scene* _scene;
		OgreWrapper::RenderScene* _renderScn;

		GameObject* _target;
		LMVector3 _offset;

		//GetCamera();
	};
}