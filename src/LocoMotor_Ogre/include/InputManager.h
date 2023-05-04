#pragma once
#ifndef INPUTMANAGER
#define INPUTMANAGER
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <vector>
#include <array>
#include "Singleton.h"

union SDL_Event;

typedef struct _SDL_GameController SDL_GameController;

namespace LocoMotor {
	enum LMScanCode;
	class MOTOR_API InputManager : public Singleton<InputManager> {
		friend Singleton<InputManager>;
	public:
		enum Axis {
			Horizontal, Vertical
		};


		// KEYBOARD
		/// @brief Returns true only in the frame that key is pressed
		bool GetKeyDown(const LMScanCode& scanCode);
		/// @brief Returns true when key is pressed
		bool GetKey(const LMScanCode& scanCode);
		/// @brief Returns true when key is stop pressed
		bool GetKeyUp(const LMScanCode& scanCode);

		// MOUSE
		/// @brief Returns true only in the frame that mouse is pressed
		bool GetMouseButtonDown(const int& buttonCode);
		/// @brief Returns true when mouse is pressed
		bool GetMouseButton(const int& buttonCode);
		/// @brief Returns true when mouse is stop pressed
		bool GetMouseButtonUp(const int& buttonCode);
		/// @brief Returns the position of the mouse in screen
		std::pair<int, int> GetMousePos();

		// Controller

		/// @brief Returns true only in the frame that controller button is pressed
		bool GetButtonDown(const int& buttonCode);
		/// @brief Returns true when controller button is pressed
		bool GetButton(const int& buttonCode);
		/// @brief Returns true when controller button is stop pressed
		bool GetButtonUp(const int& buttonCode);
		/// @brief Returns the inclination value of the joystick
		/// @param joystickIndex 0 -> left joystick | 1 ->right joystick
		/// @param axis Horizontal o Vertical
		float GetJoystickValue(const int& joystickIndex, const Axis& axis);
		/// @brief Returns the inclination value of the joystick
		/// @param triggerIndex 0 -> left trigger | 1 ->right trigger
		float GetTriggerValue(const int& triggerIndex);


		// EVENT MANAGER

		/// @brief Returns true when controller is connected
		bool ControllerConnected();

		// Registra todos los eventos relacionados con input en este frame, los recorre uno a uno
		// Almacenandolos en sus respectivas variables

		/// @brief Register all input related events  
		bool RegisterEvents();

		// Gestion de eventos de teclado
		void ManageKeyboardEvents(const SDL_Event& event);
		// Gestion de eventos de mando
		void ManageControllerEvents(const SDL_Event& event);
		// Gestion de eventos de raton
		void ManageMouseEvents(const SDL_Event& event);

		// Establece el mando conectado para su uso. Devuelve true si se puede utilizar
		bool ControllerDeviceAdded(const int32_t& controller);
		// Elimina el mando especificado
		void ControllerDeviceRemoved(const int32_t& controller);

		// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False
		void ResetKeyboardInputs();
		// Los botones que hayan llamado a los eventos SDL_MOUSEBUTTONDOWN y SDL_MOUSEBUTTONUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False
		void ResetMouseInputs();
		// Los botones que hayan llamado a los eventos SDL_CONTROLLERBUTTONDOWN y SDL_CONTROLLERBUTTONUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False
		void ResetControllerInputs();



		// FUNCIONALIDADES DE MANDO EXTRA

		// Luz LED
		void SetControllerLedColor(int r, int g, int b);

		// Vibracion
		void RumbleController(const float& intensity, const float& durationInSec);

		// Giroscopio

		// Esta funcion comunica al manager que se quiere hacer uso del giroscopio cuando se conecte un mando
		void ActivateGyroscopeWhenConnected();
		// Esta funcion se encarga de comprobar si el mando conectado tiene giroscopio implementado y lo activa en caso de tenerlo
		bool EnableControllerGyroscope();
		// Esta funcion se encarga de desactivar la funcionalidad del giroscopio
		bool DisableControllerGyroscope();
		// Devuelve el angulo actual normalizado del giroscopio del mando, significando
		// 1 : 90 grados // -1 : -90 grados
		float GetGyroscopeAngle(const Axis& axis = Horizontal);
		// Devuelve la velocidad angular del giroscopio del mando
		float GetGyroscopeAngularSpeed(const Axis& axis = Horizontal);

		void ResetGyroscope();

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

		KeyState _mouseButtons[6];

		SDL_GameController* _currentController = nullptr;

		// Vector que almacena que teclas deben ser refrescadas despues de cada frame
		std::vector<int> _keyboardInputs_ToReset;

		// Vector que almacena que botones del raton deben ser refrescadas despues de cada frame
		std::vector<int> _mouseInputs_ToReset;

		// Vector que almacena que botones del mando deben ser refrescadas despues de cada frame
		std::vector<int> _controllerInputs_ToReset;

		// Posicion del raton en la pantalla
		std::pair<int, int>_mousePos;

		// Joysticks
		float _joystickAxis[4]; // cuatro espacios : dos ejes en cada uno de los dos joysticks
		const int _JOYSTICKDEADZONE_MIN = 10000;
		const int _JOYSTICKDEADZONE_MAX = 32000;

		// Triggers
		float _triggersValue[2];
		const int _TRIGGERSVALUE_MIN = 0;
		const int _TRIGGERSVALUE_MAX = 64000;

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