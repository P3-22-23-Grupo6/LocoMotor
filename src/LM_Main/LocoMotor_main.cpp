// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CheckML.h"

#include "windows.h"
#include "MotorApi.h"


// typedef de los metodos que vamos a encontrar en la dll del Juego
typedef const char* (CALLBACK* InitJuegoFunc)(MotorApi* m);

int exec();
int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	bool dllLoaded = false;

	MotorApi* motor = new MotorApi();
	motor->Init();
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
			// La ejecutamoss
			auto result = initJuego(motor);
			std::cout << result << std::endl;
		}
		else {
			std::cerr << "DLL EXPLICIT LOADING ERROR: '" << functionName << "' function couldn't be executed" << std::endl;
		}

		dllLoaded = true;
	}
	else {
		std::cerr << "DLL EXPLICIT LOADING ERROR: '" << dllName << "' wasn't found" << std::endl;
	}

#pragma endregion
	motor->MainLoop();
	delete motor;
	if (dllLoaded)
		FreeLibrary(juegoDeAutosDLL);

	return 0;
}
