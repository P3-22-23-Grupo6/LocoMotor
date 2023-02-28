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


// TECLADO
bool InputManager::GetKeyDown (const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].down;
}

bool InputManager::GetKey (const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].isPressed;
}

bool InputManager::GetKeyUp (const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].up;
}

// MANDO
bool InputManager::GetButtonDown (const int& buttonCode) {
	return controllerButtons[buttonCode].down;
}

bool InputManager::GetButton (const int& buttonCode) {
	return controllerButtons[buttonCode].isPressed;
}

bool InputManager::GetButtonUp (const int& buttonCode) {
	return controllerButtons[buttonCode].up;
}

float InputManager::GetJoystickAxis (const int& joystickIndex, const int& axisIndex) {

	if (joystickIndex == 0) {

		if (axisIndex == 0)
			return joystickAxis[0];
		else 
			return joystickAxis[1];
	}
	else if (joystickIndex == 1) {

		if (axisIndex == 0)
			return joystickAxis[2];
		else
			return joystickAxis[3];
	}
}

// MANEJO DE EVENTOS

bool InputManager::RegisterEvents () {

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (keyboardInputs_ToReset.size () != 0)
		ResetKeyboardInputs ();

	if (controllerInputs_ToReset.size () != 0)
		ResetControllerInputs ();


	SDL_Event event;
	while (SDL_PollEvent (&event)) {

		SDL_Scancode scanCode = event.key.keysym.scancode;

		// Eventos para salir del bucle principal
		if (event.type == SDL_QUIT || scanCode == SDL_SCANCODE_ESCAPE)
			return true;


		// Manejar todos los tipos de eventos

		// Almacenar eventos de teclado en el array "keyboardKeys"
		ManageKeyboardEvents (event);

		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
		ManageControllerEvents (event);


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

		//std::cout << "joystickAxis_0 = " << joystickAxis[0] << "\n";
		//std::cout << "joystickAxis_1 = " << joystickAxis[1] << "\n";
		//std::cout << "joystickAxis_2 = " << joystickAxis[2] << "\n";
		//std::cout << "joystickAxis_3 = " << joystickAxis[3] << "\n";
	}
}

void InputManager::ManageKeyboardEvents (const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardKeys[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			keyboardInputs_ToReset.push_back (scanCode);
		}
	}

	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardKeys[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		keyboardInputs_ToReset.push_back (scanCode);
	}
}

void InputManager::ManageControllerEvents (const SDL_Event& event) {

	if (event.type == SDL_CONTROLLERDEVICEADDED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		if (ControllerDeviceAdded (connectedDevice))
			std::cout << "Controller added" << "\n";
		else
			std::cout << "Controller could not be added: A controller is already in use" << "\n";
	}

	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		ControllerDeviceRemoved (connectedDevice);
		std::cout << "Controller removed" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = controllerButtons[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			controllerInputs_ToReset.push_back (buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = controllerButtons[buttonCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		controllerInputs_ToReset.push_back (buttonCode);
	}

	if (event.type == SDL_CONTROLLERAXISMOTION) {

		Sint16 joystickValue = event.caxis.value;

		//if (joystickValue_ < JOYSTICKDEADZONE_MIN)
		//	joystickValue_ = 0;
		//else if (joystickValue_ > JOYSTICKDEADZONE_MAX)
		//	joystickValue_ = JOYSTICKDEADZONE_MAX;


		//joystickValue = abs (joystickValue);

		//joystickValue = -25000;

		// Limitador maximo
		if (joystickValue > JOYSTICKDEADZONE_MAX)
			joystickValue = JOYSTICKDEADZONE_MAX;
		else if (joystickValue < -JOYSTICKDEADZONE_MAX)
			joystickValue = -JOYSTICKDEADZONE_MAX;

		//joystickValue = 13000;


		int axis = event.caxis.axis;
		//std::cout << "axis = " << axis << "\n";

		// Si se inclina el joystick lo suficiente, guardar su valor
		if (joystickValue > JOYSTICKDEADZONE_MIN
			|| joystickValue < -JOYSTICKDEADZONE_MIN) {

			float absJoystickValue = abs (joystickValue);
			int sign = joystickValue / absJoystickValue;

			// Convertir el valor en un valor entre 0 y 1
			float normalizedValue = ((float) (absJoystickValue - JOYSTICKDEADZONE_MIN)) / ((float) (JOYSTICKDEADZONE_MAX - JOYSTICKDEADZONE_MIN));

			normalizedValue *= sign;

			joystickAxis[axis] = normalizedValue;
		}

		else
			joystickAxis[axis] = 0;


		//if (joystickValue_ != 0) {

		//	int axis = event.caxis.axis;
		//	std::cout << "joistickValue = " << joistickValue << "\n";
		//}

	}

}

bool InputManager::ControllerDeviceAdded (const Sint32& controllerAdded) {

	if (currentGameController != nullptr)
		return false;

	currentGameController = SDL_GameControllerOpen (controllerAdded);

	//for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
	//	controllerAxes_[i] = 0.0f;

	//SDL_GameControllerEventState (SDL_ENABLE);
}

void InputManager::ControllerDeviceRemoved (const Sint32& controllerRemoved) {

	currentGameController = nullptr;

	// Eliminar inputs guardados actualmente
	for (KeyState controllerButton : controllerButtons) {
		controllerButton.down = false;
		controllerButton.isPressed = false;
		controllerButton.up = false;
	}

	//for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; ++i)
	//	controllerAxes_[i] = 0.0f;

	//SDL_GameControllerEventState (SDL_ENABLE);
}


// RESET

void InputManager::ResetKeyboardInputs () {
	for (int i = 0; i < keyboardInputs_ToReset.size (); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = keyboardInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = keyboardKeys[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keyboardInputs_ToReset.clear ();
}

void InputManager::ResetControllerInputs () {

	for (int i = 0; i < controllerInputs_ToReset.size (); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = controllerInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = controllerButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keyboardInputs_ToReset.clear ();
}
