#include "InputManager.h"
#include "SDL_Scancode.h"
#include "SDL_keyboard.h"
#include <SDL_events.h>
#include <iostream>
#include <SDL_gamecontroller.h>


InputManager* InputManager::instance_ = nullptr;

InputManager::InputManager() {
}

InputManager* InputManager::Get() {
	if (InputManager::instance_ == nullptr)  instance_ = new InputManager();
	return instance_;
}


// TECLADO
bool InputManager::GetKeyDown(const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].down;
}

bool InputManager::GetKey(const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].isPressed;
}

bool InputManager::GetKeyUp(const SDL_Scancode& scanCode) {
	return keyboardKeys[scanCode].up;
}

// MANDO
bool InputManager::GetButtonDown(const int& buttonCode) {
	return controllerButtons[buttonCode].down;
}

bool InputManager::GetButton(const int& buttonCode) {
	return controllerButtons[buttonCode].isPressed;
}

bool InputManager::GetButtonUp(const int& buttonCode) {
	return controllerButtons[buttonCode].up;
}


float InputManager::GetJoystickValue(const int& joystickIndex, const Axis& axis) {

	if (joystickIndex == 0) {

		if (axis == Horizontal)
			return joystickAxis[0];
		else if (axis == Vertical)
			return joystickAxis[1];
	}
	else if (joystickIndex == 1) {

		if (axis == Horizontal)
			return joystickAxis[2];
		else if (axis == Vertical)
			return joystickAxis[3];
	}
}

// MANEJO DE EVENTOS

bool InputManager::RegisterEvents() {

	// RESETEAR TECLAS Y BOTONES

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (keyboardInputs_ToReset.size() != 0)
		ResetKeyboardInputs();

	if (controllerInputs_ToReset.size() != 0)
		ResetControllerInputs();


	// ACTUALIZAR GIROSCOPIO EN CASO DE USARSE (variable "useGyroscope")
	// Manejar el giroscopio en caso de querer utilizarlo y tener uno disponible
	if (useGyroscope && currentController != nullptr) {

		for (int i = 0; i < 2; i++) {
			const int nAxis = 2;
			float data_[nAxis];
			SDL_GameControllerGetSensorData(currentController, SDL_SENSOR_GYRO, data_, nAxis);

			float dataValue = data_[i];

			// DEADZONE
			if (dataValue < 0.01 && dataValue > -0.01)
				dataValue = 0;

			// tener en cuenta los 6 primeros decimales
			dataValue *= roundNumber;
			dataValue = (int) dataValue;

			gyroscopeValue[i] += dataValue;
		}
	}

	// Recoger todos los eventos de esta ejecucion y procesarlos uno a uno
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		SDL_Scancode scanCode = event.key.keysym.scancode;

		// Eventos para salir del bucle principal
		if (event.type == SDL_QUIT || scanCode == SDL_SCANCODE_ESCAPE)
			return true;


		// Manejar todos los tipos de eventos

		// Almacenar eventos de teclado en el array "keyboardKeys"
		ManageKeyboardEvents(event);

		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
		ManageControllerEvents(event);


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

void InputManager::ManageKeyboardEvents(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardKeys[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			keyboardInputs_ToReset.push_back(scanCode);
		}
	}

	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = keyboardKeys[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		keyboardInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ManageControllerEvents(const SDL_Event& event) {

	if (event.type == SDL_CONTROLLERDEVICEADDED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		if (ControllerDeviceAdded(connectedDevice))
			std::cout << "Controller added" << "\n";
		else
			std::cout << "Controller could not be added: A controller is already in use" << "\n";
	}

	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {

		// Mando conectado que ha generado el evento
		Sint32 connectedDevice = event.cdevice.which;

		ControllerDeviceRemoved(connectedDevice);
		std::cout << "Controller removed" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = controllerButtons[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			controllerInputs_ToReset.push_back(buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = controllerButtons[buttonCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		controllerInputs_ToReset.push_back(buttonCode);
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

			float absJoystickValue = abs(joystickValue);
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

bool InputManager::ControllerDeviceAdded(const Sint32& controllerAdded) {

	// Si ya hay un mando conectado, ignorar este
	if (currentController != nullptr)
		return false;

	currentController = SDL_GameControllerOpen(controllerAdded);

	// Si se quiere usar el giroscopio, intentar activarlo, 
	// en caso de Error, cambiar la variable de uso del giroscopio a false
	if (useGyroscope)
		useGyroscope = EnableControllerGyroscope();

	//SDL_GameControllerEventState (SDL_ENABLE);
}

void InputManager::ControllerDeviceRemoved(const Sint32& controllerRemoved) {

	currentController = nullptr;

	// Eliminar inputs guardados actualmente
	for (KeyState controllerButton : controllerButtons) {
		controllerButton.down = false;
		controllerButton.isPressed = false;
		controllerButton.up = false;
	}

	//SDL_GameControllerEventState (SDL_ENABLE);
}


// RESET

void InputManager::ResetKeyboardInputs() {
	for (int i = 0; i < keyboardInputs_ToReset.size(); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = keyboardInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = keyboardKeys[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keyboardInputs_ToReset.clear();
}

void InputManager::ResetControllerInputs() {

	for (int i = 0; i < controllerInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = controllerInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = controllerButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	keyboardInputs_ToReset.clear();
}



// FUNCIONALIDADES DE MANDO EXTRA

// Luz LED
void InputManager::SetControllerLedColor(int r, int g, int b) {

	if (currentController != nullptr) {

		if (SDL_GameControllerHasLED(currentController))
			SDL_GameControllerSetLED(currentController, r, g, b);
		else
			std::cout << "[ERROR] Could not change LED color: currentController has not LED support";
	}
	else std::cout << "[ERROR] Could not change LED color: currentController not assigned";
}

// Vibracion
void InputManager::RumbleController(const float& intensity, const float& durationInSec) {

	if (intensity > 1 || intensity < 0) {
		std::cout << "[ERROR] Rumble intensity out of range";
		return;
	}

	Uint16 rumbleIntensity = intensity * UINT16_MAX;
	SDL_GameControllerRumble(currentController, rumbleIntensity, rumbleIntensity, durationInSec * 1000);
}

// Giroscopio

// Esta funcion comunica al manager que se quiere hacer uso del giroscopio cuando se conecte un mando
void InputManager::ActivateGyroscopeWhenConnected() {
	useGyroscope = true;
}

// Esta funcion se encarga de comprobar si el mando conectado tiene giroscopio implementado y lo activa en caso de tenerlo
bool InputManager::EnableControllerGyroscope() {

	if (currentController != nullptr) {

		if (SDL_GameControllerHasSensor(currentController, SDL_SENSOR_GYRO) == SDL_TRUE) {
			SDL_GameControllerSetSensorEnabled(currentController, SDL_SENSOR_GYRO, SDL_TRUE);
			std::cout << "Gyroscope enabled in currentController" << "\n";
		}
		else {
			std::cout << "[ERROR] Could not enable controller gyroscope: currentController has not Gyroscope support" << "\n";;
			return false;
		}
	}
	else {
		std::cout << "[ERROR] Could not enable controller gyroscope: currentController not assigned" << "\n";;
		return false;
	}
}

// Esta funcion se encarga de desactivar la funcionalidad del giroscopio
bool InputManager::DisableControllerGyroscope() {
	if (currentController != nullptr) {
		if (SDL_GameControllerHasSensor(currentController, SDL_SENSOR_GYRO) == SDL_TRUE) {
			SDL_GameControllerSetSensorEnabled(currentController, SDL_SENSOR_GYRO, SDL_FALSE);
			std::cout << "Gyroscope disabled in currentController" << "\n";
		}
		else {
			std::cout << "[ERROR] Could not disable controller gyroscope: currentController has not Gyroscope support" << "\n";;
			return false;
		}
	}
	else {
		std::cout << "[ERROR] Could not disable controller gyroscope: currentController not assigned" << "\n";;
		return false;
	}
}

// Devuelve un valor desde -1 a 1 dependiendo de la velocidad del giroscopio seleccionado
float InputManager::GetGyroscopeAngularVelocity(const Axis& axis) {
	//if (axis == Horizontal)
	//else if (axis == Vertical)
	return gyroscopeAngularVelocity[0];
}

// Devuelve el angulo actual normalizado significando
// 1 : 90 grados // -1 : -90 grados
float InputManager::GetGyroscopeAngle(const Axis& axis) {

	int gyroscopeIndex = -1;
	if (axis == Vertical)
		gyroscopeIndex = 0;
	else if (axis == Horizontal)
		gyroscopeIndex = 1;

	// Convertir el valor output a un valor entre -1 y 1
	const int MAXGYROSCOPEVALUE = 350;
	float outputValue = (gyroscopeValue[gyroscopeIndex] / roundNumber);

	// Limitar el valor maximo
	//if (outputValue > MAXGYROSCOPEVALUE)
	//	outputValue = MAXGYROSCOPEVALUE;
	//else if (outputValue < -MAXGYROSCOPEVALUE)
	//	outputValue = -MAXGYROSCOPEVALUE;

	return outputValue / MAXGYROSCOPEVALUE;
}