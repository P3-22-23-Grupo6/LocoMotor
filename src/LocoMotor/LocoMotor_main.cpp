// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"		//No se que tan legal seria hacer esto supongo el manager deberia incluir ya el listener pero habra que consultarlo nose me tengo que ir
#include "InputManager.h"
#include "CheckML.h"
#include "BulletManager.h"


int exec ();
int initBullet ();

int main () {

	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	auto audio = FmodWrapper::AudioManager::Init ();
	audio->AddSound (0, "Assets/A.wav");
	auto list = FmodWrapper::AudioListener (audio);

	OgreWrapper::OgreManager::init ("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::getInstance ();
	man->createScene ("Escena");
	man->createScene ("Escena2");

	OgreWrapper::Scene* x = man->getScene ("Escenah");
	std::cout << (x == nullptr ? "null\n" : "jiji\n");
	//exec();
	//initBullet ();
	// man->render ();
	BulletWrapper::BulletManager::InitBullet ();
	BulletWrapper::RigidBodyInfo bInfo;
	BulletWrapper::BulletManager::CreateRigidBody ();
	uint32_t i = 0;

	// AudioManager::Get ()->PlaySound (0);
	while (i < 0x00000200) {

		// AUDIO
		list.UpdateFunni (.05f);
		audio->Update (0.0f);

		// RENDER
		man->render ();

		// INPUT
		if (InputManager::Get ()->PollEvents ())
			break;
		bool buttonPressed = InputManager::Get ()->GetKeyDown (SDL_SCANCODE_A);

		//std::cout << buttonPressed;


		i++;
	}
	audio->Clear ();

	return 0;
}
