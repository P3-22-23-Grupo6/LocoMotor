#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

MOTOR_API class MotorApi {
public:
	MOTOR_API MotorApi();
	MOTOR_API void init();

	MOTOR_API void RegisterGame(const char* gameName);

private:
	std::string _gameName;
};

