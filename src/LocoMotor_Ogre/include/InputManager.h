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
	KeyState keyboard[SDL_NUM_SCANCODES];

	// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de los botones del mando
	KeyState buttons_[SDL_CONTROLLER_BUTTON_MAX];

	SDL_GameController* controller_ = nullptr;

	// Vector que almacena que teclas deben ser refrescadas despues de cada frame
	std::vector<int> keysToReset;

public:

	// Referencia a la instancia de InputManager, en caso de no existir, crea una
	static InputManager* Get ();

	// Metodos principales para el uso de este manager
	// Devuelve true solo el frame en el que se presiona la tecla
	bool GetKeyDown (const SDL_Scancode& scanCode);
	// Devuelve true siempre que la tecla este presionada
	bool GetKey (const SDL_Scancode& scanCode);
	// Devuelve true solo el frame en el que se deja de presionar la tecla
	bool GetKeyUp (const SDL_Scancode& scanCode);


	// Registra todos los eventos relacionados con input en este frame, los recorre uno a uno
	// Almacenandolos en sus respectivas variables
	bool RegisterEvents ();

	// Almacena el evento de teclado registrado en la variable referenciada "event" en el array keys
	void ManageKeyboardEvents (const SDL_Event& event);
	void ManageControllerEvents (const SDL_Event& event);


	// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
	// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
	// la funcion de este metodo es resetear esas variables y ponerlas a False
	void ResetKeys ();



	void manageControllerAdded (const SDL_Event& event);

	static void Destroy () {
		delete InputManager::instance_;
	}
};

#endif // !INPUTMANAGER