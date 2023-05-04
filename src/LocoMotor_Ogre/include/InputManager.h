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

		/// @brief Register all input related events and save it in the respective value
		bool RegisterEvents();

		/// @brief Manages keyboard events
		void ManageKeyboardEvents(const SDL_Event& event);
		/// @brief Manages controller events
		void ManageControllerEvents(const SDL_Event& event);
		/// @brief Manages mouse events
		void ManageMouseEvents(const SDL_Event& event);

		/// @brief Returns true if controller is ready to use
		bool ControllerDeviceAdded(const int32_t& controller);
		/// @brief Removes the controller
		void ControllerDeviceRemoved(const int32_t& controller);

		// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False

		/// @brief Resets the last frame keyboard inputs boolean
		void ResetKeyboardInputs();
		// Los botones que hayan llamado a los eventos SDL_MOUSEBUTTONDOWN y SDL_MOUSEBUTTONUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False

		/// @brief Resets the last frame mouse inputs boolean
		void ResetMouseInputs();
		// Los botones que hayan llamado a los eventos SDL_CONTROLLERBUTTONDOWN y SDL_CONTROLLERBUTTONUP en el frame anterior,
		// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
		// la funcion de este metodo es resetear esas variables y ponerlas a False

		/// @brief Resets the last frame controller inputs boolean
		void ResetControllerInputs();



		// EXTRA CONTROLLER UTILITY

		/// @brief Sets the controller led in RGB
		void SetControllerLedColor(int r, int g, int b);

		/// @brief Sets the controller rumble with a intensity and a duration in seconds
		void RumbleController(const float& intensity, const float& durationInSec);

		// Gyroscope

		/// @brief Comunicate to the manager to active the gyroscope when controller is connected 
		void ActivateGyroscopeWhenConnected();
		/// @brief Check is the controller supports gyroscope and activate it.
		bool EnableControllerGyroscope();
		/// @brief Desactivate the gyroscope
		bool DisableControllerGyroscope();
		/// @brief Returns the normalized angle of the gyroscope
		/// @param axis 
		/// @return 1 : 90 grados // -1 : -90 grados
		float GetGyroscopeAngle(const Axis& axis = Horizontal);
		/// @brief Gets the angular speed of the gyroscope
		/// @param axis 
		float GetGyroscopeAngularSpeed(const Axis& axis = Horizontal);
		/// @brief Resets the gyroscope
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