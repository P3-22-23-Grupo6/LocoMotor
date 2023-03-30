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

#include "windows.h"

#include "../projects/LocoMotor/MotorApi.h"
// typedef de los metodos que vamos a encontrar en la dll del Juego
typedef const char* (CALLBACK* InitJuegoFunc)();

typedef void* (CALLBACK* InitJuegoFunc)();

int exec();
using namespace PhysicsWrapper;
int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

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
	juegoDeAutosDLL = LoadLibrary(dllName);

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
			std::cerr << "DLL EXPLICIT LOADING ERROR: '" << functionName << "' function couldn't be executed" << std::endl;
		}
		FreeLibrary(juegoDeAutosDLL);
	}
	else {
		std::cerr << "DLL EXPLICIT LOADING ERROR: '" << dllName << "' wasn't found" << std::endl;
	}

//#pragma region Explicit dll loading
//
//	HINSTANCE motorDLL;
//	InitJuegoFunc initMotor;
//
//	LPCWSTR dllName;
//
//	// Esa 'L' antes del string es un prefijo que permite pasar los caracteres de una string a "long char" o "wide char"
//	// (chars que utilizan 2 bytes para guardarse en vez de 1), que es lo que usa LPCWSTR (long pointer to constant WIDE string)
//#ifdef _DEBUG
//	dllName = L"LocoMotor_d";
//#else
//	dllName = L"LocoMotor";
//#endif // _DEBUG
//
//	// Cargamos la libreria
//	motorDLL = LoadLibrary(dllName);
//
//	if (motorDLL != NULL) {
//
//		// Buscamos la funcion, notese que no hace falta hacer lo de Wide Char
//		LPCSTR functionName = LPCSTR("InitJuego");
//		initJuego = (InitJuegoFunc) GetProcAddress(motorDLL, functionName);
//
//		if (initJuego != NULL) {
//			// La ejecutamos
//			const char* result = initJuego();
//			std::cout << result << std::endl;
//		}
//		else {
//			std::cerr << "DLL EXPLICIT LOADING ERROR: '" << functionName << "' function couldn't be executed" << std::endl;
//		}
//		FreeLibrary(motorDLL);
//	}
//	else {
//		std::cerr << "DLL EXPLICIT LOADING ERROR: '" << dllName << "' wasn't found" << std::endl;
//	}
	
	MotorApi* a = new MotorApi();
	a->init();
	delete a;
	return 0;
}
