#include "InputManager.h"
#include "SDL_keyboard.h"
#include <SDL_events.h>


InputManager* InputManager::instance_ = 0;

InputManager::InputManager () {
}

void InputManager::manageKeys (const SDL_Event& event) {
	//if (event.type == SDL_KEYDOWN) {
	//	SDL_Scancode code = event.key.keysym.scancode;
	//	if (!keys_[code].pressed_) {
	//		keys_[code].down_ = true;
	//		keys_[code].up_ = false;
	//		keys_[code].pressed_ = true;
	//		keysDownToFlush.push_back (code);
	//	}
	//}
	//else if (event.type == SDL_KEYUP) {
	//	SDL_Scancode code = event.key.keysym.scancode;
	//	keys_[code].down_ = false;
	//	keys_[code].pressed_ = false;
	//	keys_[code].up_ = true;
	//	keysUpsToFlush.push_back (code);
	//}
}