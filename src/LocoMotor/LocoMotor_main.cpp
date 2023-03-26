// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "PhysicsManager.h"
#include "BulletRigidBody.h"
#include "lmVector.h"
#include "RenderScene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "LocoMotor_Lua/include/ScriptManager.h"

#include "windows.h"

// typedef de los metodos que vamos a encontrar en la dll del Juego
typedef const char* (CALLBACK* InitJuegoFunc)();
typedef int(CALLBACK* NoSeQuePeroSigueSiendoDelJuego)(const char* name);

int exec();
using namespace PhysicsWrapper;
int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	//auto audio = FmodWrapper::AudioManager::Init(8);
	////audio->AddSound(0, "Assets/si.wav");
	//////new int();
	//OgreWrapper::OgreManager::Init("Prueba");
	LocoMotor::ScriptManager* sMan = LocoMotor::ScriptManager::Init();
	sMan->LoadSceneFromFile("Assets/scene.lua");
	LocoMotor::ScriptManager::Clear();
	return 0;
#pragma region Explicit dll loading

	HINSTANCE juegoDeAutosDLL;
	InitJuegoFunc initJuego;

	LPCWSTR dllName;

	// Esa 'L' antes del string es un prefijo que permite pasar los caracteres de una string a "long char" o "wide char"
	// (chars que utilizan 2 bytes para guardarse en vez de 1), que es lo que usa LPCWSTR (long pointer to constant WIDE string)
#ifdef _DEBUG
	dllName = L"Juego_de_autos_d";
#else
	dllName = L"Juego_de_autos";
#endif // _DEBUG

	// Cargamos la libreria
	juegoDeAutosDLL = LoadLibraryW(dllName);
	if (juegoDeAutosDLL != NULL) {

		// Buscamos la funcion, notese que no hace falta hacer lo de Wide Char
		LPCSTR functionName = LPCSTR("InitJuego");
		initJuego = (InitJuegoFunc) GetProcAddress(juegoDeAutosDLL, functionName);

		if (initJuego != NULL) {
			// La ejecutamos
			auto result = initJuego();
			std::cout << result << std::endl;
		}
		else {
			std::cerr << "DLL EXPLICIT LOADING ERROR: " << functionName << " function couldn't be executed" << std::endl;
		}
		FreeLibrary(juegoDeAutosDLL);
	}
	else {
		std::cerr << "DLL EXPLICIT LOADING ERROR: " << dllName << " wasn't found" << std::endl;
	}

#pragma endregion

	auto audio = FmodWrapper::AudioManager::Init(8);
	audio->AddSound(0, "Assets/si.wav");
	////new int();
	OgreWrapper::OgreManager::Init("Prueba");
	//OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::GetInstance();
	//OgreWrapper::RenderScene* x = man->CreateScene("Escena");
	//x->Prueba();
	//man->SetActiveScene(x);
	//std::cout << (x == nullptr ? "null\n" : "jiji\n");
	//PhysicsManager::Init();
	//auto btmngr = PhysicsManager::GetInstance();
	//RigidBodyInfo info1;
	//info1.boxSize = btVector3(50, 50, 50);
	//info1.mass = 0.0f;
	//info1.origin = btVector3(0, -50, 0);
	//btmngr->CreateRigidBody(info1);
	//RigidBodyInfo info2;
	//info2.size = 1.0;
	//info2.mass = 1.0f;
	//info2.origin = btVector3(2, 10, 0);
	//BulletRigidBody* bola = btmngr->CreateRigidBody(info2);

	//LocoMotor::SceneManager* mSM = new LocoMotor::SceneManager();
	//mSM->CreateScene("Escena");
	//mSM->ChangeScene("Escena");


	////audioSrc.PlaySound(0, -1);

	//InputManager* input = InputManager::Get();

	//LocoMotor::GameObject* gObj = new LocoMotor::GameObject();

	//gObj->AddComponent<LocoMotor::AudioListener>();
	//gObj->AddComponent<LocoMotor::AudioSource>();

	//float frc = 1;
	//// Activa la variable de uso del giroscopio, en el momento en el que detecte el mando, 
	//// intentara activar el giroscopio automaticamente si el mando conectado tiene giroscopio
	//input->ActivateGyroscopeWhenConnected();
	//while (true) {

	//	// INPUT
	//	if (input->RegisterEvents())
	//		break;
	//	bool buttonPressed = input->GetKeyDown(SDL_SCANCODE_A);

	//	if (input->GetKey(SDL_SCANCODE_A) || input->GetButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
	//		frc += 0.005f;
	//	}
	//	else if (input->GetKey(SDL_SCANCODE_S) || input->GetButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
	//		frc -= 0.005f;
	//	}
	//	float variation = frc + ((float(std::rand() % 11) - 5) / 300.f);
	//	//audioSrc.SetSoundFreq(0, frc);
	//	// std::cout << frc << std::endl;

	//	// AUDIO
	//	// list.Prueba(.05f);
	//	audio->Update(0.0f);
	//	//bola->setRotation(bola->getRotation() + LMQuaternion(0, 0.1, 0, 0));

	//	// RENDER
	//	//man->Render();
	//	btmngr->Update();
	//	mSM->Update();
	//	// DEMO TECNICA

	//	// Giroscopio
	//	float currentGyroscope = input->GetGyroscopeAngle(InputManager::Horizontal);
	//	//std::cout << "GIROSCOPIOSSS = " << currentGyroscope << "\n";

	//	// Clampear valor
	//	float intensity = abs(currentGyroscope);
	//	if (intensity > 1) intensity = 1;

	//	// Vibrar mando
	//	//if (currentGyroscope > .3 || currentGyroscope < -.3)
	//	//	InputManager::Get()->RumbleController(intensity, .01);

	//	// Color LED
	//	input->SetControllerLedColor(intensity * 255, 0, (1 - intensity) * 255);

	//	if (input->controllerConnected() && input->GetButtonDown(SDL_CONTROLLER_BUTTON_X)) {
	//		gObj->GetComponent<LocoMotor::AudioSource>()->Play(0);
	//	}
	//}
	//delete mSM;
	//FmodWrapper::AudioManager::Clear();
	//OgreWrapper::OgreManager::Clear();
	//PhysicsManager::Clear();
	//InputManager::Destroy();


	return 0;
}
