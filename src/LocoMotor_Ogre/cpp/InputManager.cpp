#include "InputManager.h"
#include "SDL_Scancode.h"
//#include "SDL_keyboard.h"
#include <SDL_events.h>


InputManager* InputManager::instance_ = nullptr;

InputManager::InputManager () {
}

InputManager* InputManager::Get () {
	if (InputManager::instance_ == nullptr)  instance_ = new InputManager ();
	return instance_;
}


bool InputManager::GetKeyDown (const SDL_Scancode& code) {
	return keys_[code].down_;
}

bool InputManager::GetKey (const SDL_Scancode& code) {
	return keys_[code].pressed_;
}

bool InputManager::GetKeyUp (const SDL_Scancode& code) {
	return keys_[code].up_;
}

// Almacena el evento de teclado registrado en la variable referenciada "event" en el array keys
void InputManager::ManageKey (const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode code = event.key.keysym.scancode;
		if (!keys_[code].pressed_) {
			keys_[code].down_ = true;
			keys_[code].pressed_ = true;
			keys_[code].up_ = false;
			keysToReset.push_back (code);
		}
	}
	else if (event.type == SDL_KEYUP) {
		SDL_Scancode code = event.key.keysym.scancode;
		keys_[code].down_ = false;
		keys_[code].pressed_ = false;
		keys_[code].up_ = true;
		keysToReset.push_back (code);
	}
}

// Registra todos los eventos relacionados con input en este frame, los recorre uno a uno
// Almacenandolos en sus respectivas variables
bool InputManager::PollEvents () {

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (keysToReset.size () != 0)
		ResetKeys ();

	SDL_Event event;
	while (SDL_PollEvent (&event)) {
		if (event.type == SDL_QUIT)
			return true;

		// Input managment, cambiar en caso de mando
		// Almacenar eventos de teclado en el array keys
		ManageKey (event);

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

void InputManager::ResetKeys () {
	for (int i = 0; i < keysToReset.size (); i++) {
		//KeyState thisKey = keys_[i];
		//thisKey.up_ = false;
		//thisKey.down_ = false;

		int keyCode = keysToReset[i];

		keys_[keyCode].up_ = false;
		keys_[keyCode].down_ = false;
	}

	// Limpiar las teclas ya reseteadas
	keysToReset.clear ();
}