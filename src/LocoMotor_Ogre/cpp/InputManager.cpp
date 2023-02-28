#include "InputManager.h"
#include "SDL_Scancode.h"
//#include "SDL_keyboard.h"
#include <SDL_events.h>
#include <iostream>
#include <SDL_gamecontroller.h>


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


		SDL_Scancode scanCode = event.key.keysym.scancode;

		if (event.type == SDL_QUIT || scanCode == SDL_SCANCODE_ESCAPE)
			return true;

		std::cout << SDL_IsGameController (0) << "\n";
		std::cout << "NUM JOYSTICKS = " << SDL_NumJoysticks () << "\n";


		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			std::cout << "CONTROLLER ADDED" << "\n";
			manageControllerAdded (event);
		}

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
			std::cout << "BUTTON PRESSED" << "\n";

		if (event.type == SDL_CONTROLLERAXISMOTION)
			std::cout << "SDL_CONTROLLERAXISMOTION" << "\n";


		if (event.type == SDL_JOYAXISMOTION)
			std::cout << "SDL_CONTROLLERAXISMOTION" << "\n";

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_X1:
					break;
				case SDL_BUTTON_X2:
					break;
			}
			std::cout << "MOUSE " << "\n";
		}

		else

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
		KeyState& thisKey = keyboard[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keysToReset.clear ();
}



// MANDO

void InputManager::manageControllerAdded (const SDL_Event& event) {
	if (controller_ == nullptr) {
		controller_ = SDL_GameControllerOpen (event.cdevice.which);
		//for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
		//	controllerAxes_[i] = 0.0f;

		SDL_GameControllerEventState (SDL_ENABLE);
	}
}