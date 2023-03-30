#pragma once
#define MOTOR_API __declspec(dllexport)
MOTOR_API class MotorApi {
public:
	MOTOR_API MotorApi();
	MOTOR_API void init();
};

