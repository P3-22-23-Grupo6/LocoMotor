#include "InputManager.h"
#include "SDL_Scancode.h"
//#include "SDL_keyboard.h"
#include <SDL_events.h>


InputManager* InputManager::instance_ = nullptr;

InputManager::InputManager () {
}

InputManager* InputManager::Get () {
	if(InputManager::instance_==nullptr)  instance_ = new InputManager ();
	return instance_;
}


bool InputManager::GetKeyDown (const SDL_Scancode& code) {
	return keys_[code].down_;
}

bool InputManager::GetKeyUp (const SDL_Scancode& code) {
	return keys_[code].up_;
}


void InputManager::ManageKeys (const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode code = event.key.keysym.scancode;
		if (!keys_[code].pressed_) {
			keys_[code].down_ = true;
			keys_[code].up_ = false;
			keys_[code].pressed_ = true;
			//keysDownToFlush.push_back (code);
		}
	}
	else if (event.type == SDL_KEYUP) {
		SDL_Scancode code = event.key.keysym.scancode;
		keys_[code].down_ = false;
		keys_[code].pressed_ = false;
		keys_[code].up_ = true;
		//keysUpsToFlush.push_back (code);
	}
}

bool InputManager::PollEvents () {

	SDL_Event event;
	//InputManager::getInstance ()->flushInput ();
	while (SDL_PollEvent (&event)) {
		if (event.type == SDL_QUIT)
			return true;

		// Input managment, cambiar en caso de mando
		ManageKeys (event);

		//switch (event.type)
		//{
		//case sdl_quit:
			//root_->queueEndRendering();
		//	return true;

		//	break;
		//default:
		//	InputManager::getInstance()->generalInputManagement(event);

		//	return false;
		//	break;
		//}

	}
}