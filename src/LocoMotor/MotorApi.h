#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>


namespace LocoMotor {
	class SceneManager;
	class GameObject;
}

MOTOR_API class MotorApi {
public:
	MOTOR_API MotorApi();
	MOTOR_API void init();
	MOTOR_API void Init();

	MOTOR_API void RegisterGame(const char* gameName);

	/// @brief Dont use it
	/// @return please
	MOTOR_API void MainLoop();

	//template <typename T>
	//MOTOR_API void RegisterComponent() {
	//	ComponentsFactory::GetInstance()->RegisterComponent<T>();
	//}
private:
	void Prueba(float a);
	std::string _gameName;

	LocoMotor::SceneManager* _scnManager;

	std::string _startScene;
	LocoMotor::GameObject* enemy_gObj;
	bool _exit;
};

