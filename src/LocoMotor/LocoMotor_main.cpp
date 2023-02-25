// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CheckML.h"
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"		//No se que tan legal seria hacer esto supongo el manager deberia incluir ya el listener pero habra que consultarlo nose me tengo que ir
#include "InputManager.h"
#include "RenderScene.h"

int exec ();
int initBullet ();

int main () {

	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	/*AudioManager::Get ()->AddSound (0, "A.wav");
	auto list = AudioListener (AudioManager::Get ());*/

	OgreWrapper::OgreManager::Init ("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::GetInstance ();
	/*OgreWrapper::RenderScene* x = man->CreateScene ("Escena");
	man->SetActiveScene (x);
	x ->Prueba ();*/
	//exec();
	//initBullet ();
	// man->render ();

	//AudioManager::Get ()->PlaySound (0);
	while (true) {

		// AUDIO
		/*list.UpdateFunni (.000003f);
		AudioManager::Get ()->Update (0.0f);*/

		// RENDER
		//man->Render ();

		// INPUT
		if (InputManager::Get ()->PollEvents ())
			break;
		bool buttonPressed = InputManager::Get ()->GetKeyDown (SDL_SCANCODE_A);

		std::cout << buttonPressed;
	}

	man->Shutdown ();
	InputManager::Destroy ();
	return 0;
}
