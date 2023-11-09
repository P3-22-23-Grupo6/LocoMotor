#include "InputManager.h"
#include "SDL_Scancode.h"
#include "SDL_keyboard.h"
#include <SDL_events.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include "LMInputs.h"

using namespace LocoMotor;

LocoMotor::InputManager* Singleton<LocoMotor::InputManager>::_instance = nullptr;

InputManager::InputManager() {
	_gyroscopeValue[0] = 0.f;
	_gyroscopeValue[1] = 0.f;
	_gyroscopeVelocityValue[0] = 0.f;
	_gyroscopeVelocityValue[1] = 0.f;
	_joystickAxisOne[0] = 0.f;
	_joystickAxisTwo[1] = 0.f;
	_joystickAxisOne[2] = 0.f;
	_joystickAxisTwo[3] = 0.f;
	_triggersValueOne[0] = 0.f;
	_triggersValueTwo[1] = 0.f;
	_mousePos.first = 0;
	_mousePos.second = 0;
}


// TECLADO
bool InputManager::GetKeyDown(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].down;
}

bool InputManager::GetKey(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].isPressed;
}

bool InputManager::GetKeyUp(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].up;
}

// RATON
bool InputManager::GetMouseButtonDown(const int& buttonCode) {
	return _mouseButtons[buttonCode].down;
}

bool InputManager::GetMouseButton(const int& buttonCode) {
	return _mouseButtons[buttonCode].isPressed;
}

bool InputManager::GetMouseButtonUp(const int& buttonCode) {
	return _mouseButtons[buttonCode].up;
}

std::pair<int, int> LocoMotor::InputManager::GetMousePos() {
	return _mousePos;
}

// MANDO
bool InputManager::GetButtonDown(int index, const int& buttonCode) {
	if(index == 0)return _controllerButtonsOne[buttonCode].down;
	else return _controllerButtonsTwo[buttonCode].down;
	
}

bool InputManager::GetButton(int index, const int& buttonCode) {
	if (index == 0)return _controllerButtonsOne[buttonCode].isPressed;
	else return _controllerButtonsTwo[buttonCode].isPressed;
}

bool InputManager::GetButtonUp(int index, const int& buttonCode) {
	if (index == 0) return _controllerButtonsOne[buttonCode].up;
	else return _controllerButtonsTwo[buttonCode].up;
}


float InputManager::GetJoystickValue(int index, const int& joystickIndex, const Axis& axis) {
	if (index == 0) {
		if (joystickIndex == 0) {

			if (axis == Horizontal)
				return _joystickAxisOne[0];
			else if (axis == Vertical)
				return _joystickAxisOne[1];
		}
		else if (joystickIndex == 1) {

			if (axis == Horizontal)
				return _joystickAxisOne[2];
			else if (axis == Vertical)
				return _joystickAxisOne[3];
		}
		return 0.f;
	}
	else {
		if (joystickIndex == 0) {

			if (axis == Horizontal)
				return _joystickAxisTwo[0];
			else if (axis == Vertical)
				return _joystickAxisTwo[1];
		}
		else if (joystickIndex == 1) {

			if (axis == Horizontal)
				return _joystickAxisTwo[2];
			else if (axis == Vertical)
				return _joystickAxisTwo[3];
		}
		return 0.f;
	}
	
}

float LocoMotor::InputManager::GetTriggerValue(int index, const int& triggerIndex) {
	if (index == 0) {
		if (triggerIndex == 0 || triggerIndex == 1)return _triggersValueOne[triggerIndex];
		return 0.0f;
	}
	else{
		if (triggerIndex == 0 || triggerIndex == 1)return _triggersValueTwo[triggerIndex];
		return 0.0f;
	}
}

// MANEJO DE EVENTOS

bool InputManager::ControllerConnected(int index) {
	return index == 0 ? _controllerOne != nullptr : _controllerTwo != nullptr;
}

bool InputManager::RegisterEvents() {
	
	// RESETEAR TECLAS Y BOTONES

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (_keyboardInputs_ToReset.size() != 0)
		ResetKeyboardInputs();

	if (_mouseInputs_ToReset.size() != 0)
		ResetMouseInputs();

	if (_controllerInputs_ToReset.size() != 0)
		ResetControllerInputs();


	//// ACTUALIZAR GIROSCOPIO EN CASO DE USARSE (variable "useGyroscope")
	//// Manejar el giroscopio en caso de querer utilizarlo y tener uno disponible
	//if (ControllerConnected(index) && _useGyroscope) {
	//	SDL_GameController* cont = index == 0 ? _controllerOne : _controllerTwo;
	//	for (int i = 0; i < 2; i++) {
	//		const int nAxis = 2;
	//		float data_[nAxis];
	//		SDL_GameControllerGetSensorData(cont, SDL_SENSOR_GYRO, data_, nAxis);

	//		_gyroscopeVelocityValue[i] = data_[i];

	//		float& thisData = _gyroscopeVelocityValue[i];

	//		// DEADZONE
	//		if (thisData < 0.01 && thisData > -0.01)
	//			thisData = 0;

	//		// tener en cuenta los 6 primeros decimales
	//		thisData *= _roundNumber;
	//		thisData = std::roundf(thisData);



	//		_gyroscopeValue[i] += thisData;

	//	}
	//}

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

		// Gestionar eventos del raton
		ManageMouseEvents(event);

	}
	return false;
}

void InputManager::ManageKeyboardEvents(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			_keyboardInputs_ToReset.push_back(scanCode);
		}
	}

	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		_keyboardInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ManageControllerEvents(const SDL_Event& event) {

	SDL_JoystickID joystickID = event.jdevice.which;
	std::cout << "\n :" << joystickID << "\n";
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
		KeyState& thisButton = joystickID == 0 ? _controllerButtonsOne[buttonCode] : _controllerButtonsTwo[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			_controllerInputs_ToReset.push_back(buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		KeyState& thisButton = joystickID == 0 ? _controllerButtonsOne[buttonCode] : _controllerButtonsTwo[buttonCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		_controllerInputs_ToReset.push_back(buttonCode);
	}

	if (event.type == SDL_CONTROLLERAXISMOTION) {

		Sint16 joystickValue = event.caxis.value;

		// Limitador maximo
		if (joystickValue > _JOYSTICKDEADZONE_MAX)
			joystickValue = _JOYSTICKDEADZONE_MAX;
		else if (joystickValue < -_JOYSTICKDEADZONE_MAX)
			joystickValue = -_JOYSTICKDEADZONE_MAX;




		int axis = event.caxis.axis;
		if (axis < 4) {
			// Si se inclina el joystick lo suficiente, guardar su valor
			if (joystickValue > _JOYSTICKDEADZONE_MIN
				|| joystickValue < -_JOYSTICKDEADZONE_MIN) {

				float absJoystickValue = fabsf(joystickValue);
				int sign = (int)(joystickValue / absJoystickValue);

				// Convertir el valor en un valor entre 0 y 1
				float normalizedValue = ((float)(absJoystickValue - _JOYSTICKDEADZONE_MIN)) / ((float)(_JOYSTICKDEADZONE_MAX - _JOYSTICKDEADZONE_MIN));

				normalizedValue *= sign;

				if(joystickID == 0) _joystickAxisOne[axis] = normalizedValue;
				else _joystickAxisTwo[axis] = normalizedValue;
			}

			else{
				if (joystickID == 0)_joystickAxisOne[axis] = 0;
				else _joystickAxisTwo[axis] = 0;
			}
		}

	}
	if (event.type == SDL_JOYAXISMOTION) {

		Sint16 triggerValue = event.jaxis.value;



		int axis = event.jaxis.axis;
		if (axis > 3) {
			axis -= 4;
			float auxValue = triggerValue + _TRIGGERSVALUE_MAX / 2.f;
			if (joystickID == 0)
				if (axis == 0 || axis == 1)_triggersValueOne[axis] = auxValue / _TRIGGERSVALUE_MAX;
			else if (axis == 0 || axis == 1)_triggersValueTwo[axis] = auxValue / _TRIGGERSVALUE_MAX;
		}


	}

}

void InputManager::ManageMouseEvents(const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		_mousePos.first = event.motion.x;
		_mousePos.second = event.motion.y;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			_mouseInputs_ToReset.push_back(scanCode);
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		_mouseInputs_ToReset.push_back(scanCode);
	}
}

bool InputManager::ControllerDeviceAdded(const int32_t& controllerAdded) {
	
	// Si ya hay un mando conectado, ignorar este
	if (_controllerOne != nullptr)
	{
		if (_controllerTwo != nullptr) return false;
		_controllerTwo = SDL_GameControllerOpen(controllerAdded);
		// Si se quiere usar el giroscopio, intentar activarlo, 
		// en caso de Error, cambiar la variable de uso del giroscopio a false
		if (_useGyroscope)
			_useGyroscope = EnableControllerGyroscope();

		return true;
	}
		

	_controllerOne = SDL_GameControllerOpen(controllerAdded);
	// Si se quiere usar el giroscopio, intentar activarlo, 
	// en caso de Error, cambiar la variable de uso del giroscopio a false
	if (_useGyroscope)
		_useGyroscope = EnableControllerGyroscope();
	
	return true;
}

void InputManager::ControllerDeviceRemoved(const int32_t& controllerRemoved) {

	return;
	//_currentController = nullptr;

	// Eliminar inputs guardados actualmente
	for (KeyState controllerButton : _controllerButtonsOne) {
		controllerButton.down = false;
		controllerButton.isPressed = false;
		controllerButton.up = false;
	}
}


// RESET

void InputManager::ResetKeyboardInputs() {
	for (int i = 0; i < _keyboardInputs_ToReset.size(); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = _keyboardInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = _keyboardKeys[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_keyboardInputs_ToReset.clear();
}

void InputManager::ResetMouseInputs() {
	for (int i = 0; i < _mouseInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = _mouseInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = _mouseButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_mouseInputs_ToReset.clear();
}

void InputManager::ResetControllerInputs() {

	for (int i = 0; i < _controllerInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = _controllerInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = _controllerButtonsOne[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_controllerInputs_ToReset.clear();
}



// FUNCIONALIDADES DE MANDO EXTRA

// Luz LED
void InputManager::SetControllerLedColor(int r, int g, int b) {

	if (_controllerOne != nullptr) {

		if (SDL_GameControllerHasLED(_controllerOne))
			SDL_GameControllerSetLED(_controllerOne, r, g, b);
	}

}

// Vibracion
void InputManager::RumbleController(int index, const float& intensity, const float& durationInSec) {

	if (intensity > 1 || intensity < 0) {
		std::cout << "[ERROR] Could not Rumble controller: Rumble intensity out of range";
		return;
	}
	SDL_GameController* cont = index == 0 ? _controllerOne : _controllerTwo;
	if (cont != nullptr) {

		if (SDL_GameControllerHasRumble(cont)) {
			Uint16 rumbleIntensity = (Uint16)(intensity * UINT16_MAX);
			SDL_GameControllerRumble(cont, rumbleIntensity, rumbleIntensity, (Uint32)(durationInSec * 1000));
		}
		else
			std::cout << "[ERROR] Could not Rumble controller: currentController has not Rumble support";
	}
	else std::cout << "[ERROR] Could not Rumble controller: currentController not assigned";
}

// Giroscopio

void InputManager::ActivateGyroscopeWhenConnected() {
	_useGyroscope = true;
}

bool InputManager::EnableControllerGyroscope() {
	return false;
	//if (_currentController != nullptr) {

	//	if (SDL_GameControllerHasSensor(_currentController, SDL_SENSOR_GYRO) == SDL_TRUE) {
	//		SDL_GameControllerSetSensorEnabled(_currentController, SDL_SENSOR_GYRO, SDL_TRUE);
	//		std::cout << "Gyroscope enabled in currentController" << "\n";
	//		return true;
	//	}
	//	else {
	//		std::cout << "[ERROR] Could not enable controller gyroscope: currentController has not Gyroscope support" << "\n";
	//		return false;
	//	}
	//}
	//else {
	//	std::cout << "[ERROR] Could not enable controller gyroscope: currentController not assigned" << "\n";;
	//	return false;
	//}
}

bool InputManager::DisableControllerGyroscope() {
	return false;
	/*if (_currentController != nullptr) {
		if (SDL_GameControllerHasSensor(_currentController, SDL_SENSOR_GYRO) == SDL_TRUE) {
			SDL_GameControllerSetSensorEnabled(_currentController, SDL_SENSOR_GYRO, SDL_FALSE);
			std::cout << "Gyroscope disabled in currentController" << "\n";
			return true;
		}
		else {
			std::cout << "[ERROR] Could not disable controller gyroscope: currentController has not Gyroscope support" << "\n";
			return false;
		}
	}
	else {
		std::cout << "[ERROR] Could not disable controller gyroscope: currentController not assigned" << "\n";;
		return false;
	}*/
}

float InputManager::GetGyroscopeAngle(const Axis& axis) {

	int gyroscopeIndex = -1;
	if (axis == Vertical)
		gyroscopeIndex = 0;
	else if (axis == Horizontal)
		gyroscopeIndex = 1;

	// Convertir el valor output a un valor entre -1 y 1
	float outputValue = 0;
	if (gyroscopeIndex != -1)
		outputValue = _gyroscopeValue[gyroscopeIndex] / _roundNumber;

	return outputValue / _MAXGYROSCOPEVALUE;
}

float InputManager::GetGyroscopeAngularSpeed(const Axis& axis) {

	int gyroscopeIndex = -1;
	if (axis == Vertical)
		gyroscopeIndex = 0;
	else if (axis == Horizontal)
		gyroscopeIndex = 1;

	float outputValue = 0;
	if (gyroscopeIndex != -1)
		outputValue = _gyroscopeVelocityValue[gyroscopeIndex] / _roundNumber;

	return outputValue / _MAXGYROSCOPEVALUE;
}

void LocoMotor::InputManager::ResetGyroscope() {
	_gyroscopeValue[0] = 0;
	_gyroscopeValue[1] = 0;
}

