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
	return keyboardButtons[scanCode].down;
}

bool InputManager::GetKey (const SDL_Scancode& scanCode) {
	return keyboardButtons[scanCode].isPressed;
}

bool InputManager::GetKeyUp (const SDL_Scancode& scanCode) {
	return keyboardButtons[scanCode].up;
}

void InputManager::ManageKeyboardEvents (const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardButtons[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			keysToReset.push_back (scanCode);
		}
	}
	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardButtons[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		keysToReset.push_back (scanCode);
	}
}

void InputManager::ManageControllerEvents (const SDL_Event& event) {
	SDL_GameController* controller = SDL_GameControllerOpen (event.cdevice.which);

	if (event.type == SDL_CONTROLLERDEVICEADDED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		if (ControllerDeviceAdded (connectedDevice))
			std::cout << "Controller connected" << "\n";
		else
			std::cout << "Controller could not connect: A controller is already in use" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		Uint8 thisButton = 0;
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

	}

	//if (event.type == SDL_CONTROLLERBUTTONUP)
	//	std::cout << "BUTTON UP" << "\n";
}

bool InputManager::ControllerDeviceAdded (const Sint32& controllerConnected) {

	if (currentGameController != nullptr)
		return false;

	currentGameController = SDL_GameControllerOpen (controllerConnected);

	//for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
	//	controllerAxes_[i] = 0.0f;

	//SDL_GameControllerEventState (SDL_ENABLE);
}




bool InputManager::RegisterEvents () {

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (keysToReset.size () != 0)
		ResetKeys ();

	SDL_Event event;
	while (SDL_PollEvent (&event)) {

		SDL_Scancode scanCode = event.key.keysym.scancode;

		// Eventos para salir del bucle principal
		if (event.type == SDL_QUIT || scanCode == SDL_SCANCODE_ESCAPE)
			return true;


		ManageControllerEvents (event);

		// Input managment, cambiar en caso de mando
		// Almacenar eventos de teclado en el array keys
		ManageKeyboardEvents (event);

		//std::cout << "CONTROLLER CONNECTED = " << SDL_IsGameController (0) << "\n";

		//SDL_GameController* controller = SDL_GameControllerOpen (event.cdevice.which);

		//if (event.type == SDL_CONTROLLERDEVICEADDED) {
		//	std::cout << "CONTROLLER ADDED" << "\n";
		//}

		//if (event.type == SDL_CONTROLLERBUTTONDOWN)
		//	std::cout << "BUTTON DOWN" << "\n";

		//if (event.type == SDL_CONTROLLERBUTTONUP)
		//	std::cout << "BUTTON UP" << "\n";

		//if (event.type == SDL_CONTROLLERAXISMOTION)
		//	std::cout << "SDL_CONTROLLERAXISMOTION" << "\n";

		//if (event.type == SDL_JOYAXISMOTION)
		//	std::cout << "SDL_CONTROLLERAXISMOTION" << "\n";

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
	}
}

void InputManager::ResetKeys () {
	for (int i = 0; i < keysToReset.size (); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = keysToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = keyboardButtons[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keysToReset.clear ();
}
