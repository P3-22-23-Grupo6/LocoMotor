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
		/* @brief
		 * This function updates the position and rotation of a camera to follow a target object.
		 *
		 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
		 * used to ensure that the movement and updates in the game are consistent across different hardware
		 * and frame rates.
		*/
		void Update(float dt) override;

		void SetTarget(GameObject* target, LMVector3 offset);
		//Metodo de Ogre para Trackear una entidad(player)
		//void SetTracking(bool isTracking, GameObject* target, LMVector3 offset);
		void SetClippingPlane(int nearPlane, int farPlane);
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