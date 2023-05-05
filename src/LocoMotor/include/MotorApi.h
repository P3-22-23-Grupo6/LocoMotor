#pragma once

#ifndef _MOTORAPI_
#define _MOTORAPI_
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor {
	class SceneManager;
	class GameObject;


	class MotorApi {
	public:
		MOTOR_API MotorApi();
		MOTOR_API void Init();

		MOTOR_API void RegisterGame(const char* gameName);

		/// @brief Dont use it
		/// @return please
		MOTOR_API void MainLoop();
	private:

		std::string _gameName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;

		LocoMotor::GameObject* _ship_gObj;
	};
}
#endif;

