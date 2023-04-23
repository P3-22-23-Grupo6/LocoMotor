#pragma once
#ifndef INPUTMANAGER
#define INPUTMANAGER
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

//#include "LMInputs.h"
//#include <SDL_gamecontroller.h>
#include <vector>
#include <array>
#include "Singleton.h"

enum LMScanCode;

union SDL_Event;

typedef struct _SDL_GameController SDL_GameController;
//class SDL_Scancode;


namespace LocoMotor {
	class MOTOR_API InputManager : public Singleton<InputManager> {
		friend Singleton<InputManager>;
	public:

	// Referencia a la instancia de InputManager, en caso de no existir, crea una
		//static InputManager* Get();


		enum Axis {
			Horizontal, Vertical
		};

		// METODOS PRINCIPALES PARA EL USO DE INPUT

		// TECLADO
		// Devuelve true solo el frame en el que se presiona la tecla
		bool GetKeyDown(const LMScanCode& scanCode);
		// Devuelve true siempre que la tecla este presionada
		bool GetKey(const LMScanCode& scanCode);
		// Devuelve true solo el frame en el que se deja de presionar la tecla
		bool GetKeyUp(const LMScanCode& scanCode);

		// MANDO

		// Devuelve true siempre que la tecla este presionada
		bool GetButtonDown(const int& buttonCode);

		bool GetButton(const int& buttonCode);

		bool GetButtonUp(const int& buttonCode);

		float GetJoystickValue(const int& joystickIndex, const Axis& axis);


		// GESTION DE EVENTOS

		bool controllerConnected();

		// Registra todos los eventos relacionados con input en este frame, los recorre uno a uno
		// Almacenandolos en sus respectivas variables
		bool RegisterEvents();

		// Almacena el evento de teclado registrado en la variable referenciada "event" en el array keys
		void ManageKeyboardEvents(const SDL_Event& event);
		void ManageControllerEvents(const SDL_Event& event);

		bool ControllerDeviceAdded(const int32_t& controller);
		void ControllerDeviceRemoved(const int32_t& controller);

		// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False
		void ResetKeyboardInputs();

		void ResetControllerInputs();



		// FUNCIONALIDADES DE MANDO EXTRA

		// Luz LED
		void SetControllerLedColor(int r, int g, int b);

		// Vibracion
		void RumbleController(const float& intensity, const float& durationInSec);

		// Giroscopio
		void ActivateGyroscopeWhenConnected();

		bool EnableControllerGyroscope();
		bool DisableControllerGyroscope();

		float GetGyroscopeAngle(const Axis& axis = Horizontal);

		float GetGyroscopeAngularSpeed(const Axis& axis = Horizontal);

	private:
		InputManager();


		struct KeyState {
			bool down = false;
			bool isPressed = false;
			bool up = false;
		};
		// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de las teclas
		KeyState _keyboardKeys[512];

		// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de los botones del mando
		KeyState _controllerButtons[21];

		SDL_GameController* _currentController = nullptr;

		// Vector que almacena que teclas deben ser refrescadas despues de cada frame
		std::vector<int> _keyboardInputs_ToReset;

		// Vector que almacena que botones deben ser refrescadas despues de cada frame
		std::vector<int> _controllerInputs_ToReset;


		// Joysticks
		float _joystickAxis[4]; // cuatro espacios : dos ejes en cada uno de los dos joysticks
		const int _JOYSTICKDEADZONE_MIN = 10000;
		const int _JOYSTICKDEADZONE_MAX = 32000;

		// Giroscopio del mando
		bool _useGyroscope = false;
		float _gyroscopeValue[2];
		float _gyroscopeVelocityValue[2];
		const int _MAXGYROSCOPEVALUE = 200;
		// Redondear los datos del giroscopio un determinado numero de digitos
		// (Numero de digitos = Numero de ceros)
		const int _roundNumber = 1000000;


	};
}

#endif // !INPUTMANAGER