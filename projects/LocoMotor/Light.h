#pragma once
#pragma once

#include "Component.h"
#include "LMVector.h"

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
namespace OgreWrapper {
	class Light;
	class RenderScene;
	class Node;
}

namespace LocoMotor {
	class Scene;
	class GameObject;

	class MOTOR_API Light : public Component {
	public:
		// Para crear la camara se necesita tanto la escena como la escena de Render
		Light();

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

	private:
		OgreWrapper::Light* _light;
		Scene* _scene;
	};
}