#pragma once
#ifndef INPUTMANAGER
#define INPUTMANAGER

//#include "SDL_keyboard.h"
#include <vector>
#include <array>

union SDL_Event;

class InputManager {

private:
	InputManager ();

	static InputManager* instance_;

	//pendiente de agregar mandos

	struct KeyState {
		bool down_ = false;
		bool pressed_ = false;
		bool up_ = false;
	};

	void manageKeys (const SDL_Event& event);
};

#endif // !INPUTMANAGER