#pragma once
#ifndef INPUTMANAGER
#define INPUTMANAGER

#include "SDL_keyboard.h"
#include <SDL_gamecontroller.h>

#include <vector>
#include <array>

union SDL_Event;


class InputManager {

private:
	InputManager ();

	static InputManager* instance_;


	struct KeyState {
		bool down = false;
		bool isPressed = false;
		bool up = false;
	};
	// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de las teclas
	KeyState keyboardKeys[SDL_NUM_SCANCODES];

	// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de los botones del mando
	KeyState controllerButtons[SDL_CONTROLLER_BUTTON_MAX];

	SDL_GameController* currentGameController = nullptr;

	// Vector que almacena que teclas deben ser refrescadas despues de cada frame
	std::vector<int> keyboardInputs_ToReset;

	// Vector que almacena que botones deben ser refrescadas despues de cada frame
	std::vector<int> controllerInputs_ToReset;

public:

	// Referencia a la instancia de InputManager, en caso de no existir, crea una
	static InputManager* Get ();

	// METODOS PRINCIPALES PARA EL USO DE INPUT
	
	// TECLADO
	// Devuelve true solo el frame en el que se presiona la tecla
	bool GetKeyDown (const SDL_Scancode& scanCode);
	// Devuelve true siempre que la tecla este presionada
	bool GetKey (const SDL_Scancode& scanCode);
	// Devuelve true solo el frame en el que se deja de presionar la tecla
	bool GetKeyUp (const SDL_Scancode& scanCode);

	// MANDO

	// Devuelve true siempre que la tecla este presionada
	bool GetButtonDown (const int& buttonCode);

	bool GetButton (const int& buttonCode);

	bool GetButtonUp (const int& buttonCode);



	// GESTION DE EVENTOS

	// Registra todos los eventos relacionados con input en este frame, los recorre uno a uno
	// Almacenandolos en sus respectivas variables
	bool RegisterEvents ();

	// Almacena el evento de teclado registrado en la variable referenciada "event" en el array keys
	void ManageKeyboardEvents (const SDL_Event& event);
	void ManageControllerEvents (const SDL_Event& event);

	bool ControllerDeviceAdded (const Sint32& controller);
	void ControllerDeviceRemoved (const Sint32& controller);

	// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
	// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
	// la funcion de este metodo es resetear esas variables y ponerlas a False
	void ResetKeyboardInputs ();

	void ResetControllerInputs ();

	static void Destroy () {
		delete InputManager::instance_;
	}
};

#endif // !INPUTMANAGER