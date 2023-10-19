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
		Camera();

		/// @brief Inits the component with parameters from lua
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		/// @brief Inits the component
		void InitComponent() override;

		/// @brief Starts the component
		void Start() override;

		/// @brief Updates the position and rotation of a camera to follow a target object.
		/// @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
		/// used to ensure that the movement and updates in the game are consistent across different hardware
		/// and frame rates.
		void PreUpdate(float dt) override;

		/// @brief Set the target and offset for the camera of a LocoMotor object.
		/// @param target A pointer to a GameObject that the camera will follow as its target.
		/// @param offset The offset is a vector that represents the distance and direction from the target
		/// object's position where the camera should be positioned. It is used to adjust the camera's position
		/// relative to the target object.
		void SetTarget(GameObject* target, LMVector3 offset);
		//Metodo de Ogre para Trackear una entidad(player)
		//void SetTracking(bool isTracking, GameObject* target, LMVector3 offset);

		/// @brief Set the clipping plane of a camera object.
		/// @param nearPlane The distance from the camera to the nearest visible object in the scene. Any object
		/// closer than this distance will not be visible in the rendered image.
		/// @param farPlane The far clipping plane is the maximum distance from the camera at which objects will
		/// be rendered. Any objects beyond this distance will not be visible in the rendered image.
		void SetClippingPlane(int nearPlane, int farPlane);

		/// @brief Sets the field of view (FOV) of a camera object.
		/// @param newFov newFov is a float variable representing the new field of view (FOV) value that will be
		/// set for the camera. FOV is the extent of the observable world that is seen at any given moment
		/// through the camera lens. It is usually measured in degrees and determines how much of the scene
		void SetFOV(float newFov);
		void SetViewportRatio(int viewportIndex, int modeIndex);

	private:
		OgreWrapper::Camera* _cam;
		Scene* _scene;

		GameObject* _target;
		LMVector3 _initialOffset;//Offset with the Player

		std::string target = "";
	};
}