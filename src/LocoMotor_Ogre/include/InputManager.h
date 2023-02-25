#pragma once
#ifndef INPUTMANAGER
#define INPUTMANAGER

#include "SDL_keyboard.h"

#include <vector>
#include <array>

union SDL_Event;


class InputManager {

private:
	InputManager ();

	static InputManager* instance_;


	struct KeyState {
		bool down_ = false;
		bool pressed_ = false;
		bool up_ = false;
	};

	KeyState keys_[SDL_NUM_SCANCODES];


	//void manageKeyDown (const SDL_Event& event);
	//void manageKeyUp (const SDL_Event& event);

public:

	static InputManager* Get ();

	bool GetKeyDown (const SDL_Scancode& code);
	bool GetKeyUp (const SDL_Scancode& code);


	//void manageButtonDown (const SDL_Event& event);
	//void manageButtonUp (const SDL_Event& event);

	void ManageKeys (const SDL_Event& event);

	bool PollEvents ();


};

#endif // !INPUTMANAGER