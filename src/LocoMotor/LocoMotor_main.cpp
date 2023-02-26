// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"		//No se que tan legal seria hacer esto supongo el manager deberia incluir ya el listener pero habra que consultarlo nose me tengo que ir
#include "InputManager.h"
#include "CheckML.h"

int exec ();
int initBullet ();

int main () {

	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	AudioManager::Get ()->AddSound (0, "A.wav");
	auto list = AudioListener (AudioManager::Get ());

	OgreWrapper::OgreManager::init ("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::getInstance ();
	man->createScene ("Escena");
	man->createScene ("Escena2");

	OgreWrapper::Scene* x = man->getScene ("Escenah");
	std::cout << (x == nullptr ? "null\n" : "jiji\n");
	//exec();
	initBullet ();
	// man->render ();

	uint32_t i = 0;

	AudioManager::Get ()->PlaySound (0);
	while (i < 0x00300000) {

		// AUDIO
		list.UpdateFunni (.000003f);
		AudioManager::Get ()->Update (0.0f);

		// RENDER
		man->render ();

		// INPUT
		if (InputManager::Get ()->PollEvents ())
			break;
		bool buttonPressed = InputManager::Get ()->GetKeyDown (SDL_SCANCODE_A);

		std::cout << buttonPressed;


		i++;
	}

	return 0;
}
