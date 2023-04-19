#pragma once
#ifndef _LM_INPUTS
#define _LM_INPUTS
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

class InputManager;

struct Keyboard {
	
};
struct Controller {

};
struct Gyro {

};


class MOTOR_API LMInputs {
public:
	LMInputs();
	~LMInputs();
};


#endif