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

bool InputManager::GetKeyDown (const SDL_Scancode& scanCode) {
	return keyboard[scanCode].down;
}

bool InputManager::GetKey (const SDL_Scancode& scanCode) {
	return keyboard[scanCode].isPressed;
}

bool InputManager::GetKeyUp (const SDL_Scancode& scanCode) {
	return keyboard[scanCode].up;
}

void InputManager::ManageKey (const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboard[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			keysToReset.push_back (scanCode);
		}
	}
	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboard[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		keysToReset.push_back (scanCode);
	}
}

bool InputManager::RegisterEvents () {

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (keysToReset.size () != 0)
		ResetKeys ();

	SDL_Event event;
	while (SDL_PollEvent (&event)) {
		if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return true;

		// Input managment, cambiar en caso de mando
		// Almacenar eventos de teclado en el array keys
		ManageKey (event);
	}
}

void InputManager::ResetKeys () {
	for (int i = 0; i < keysToReset.size (); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = keysToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState &thisKey = keyboard[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keysToReset.clear ();
}