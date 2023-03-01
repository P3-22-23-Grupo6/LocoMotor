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
using namespace BulletWrapper;
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
	BulletManager::Init ();
	//auto btmngr = BulletManager::GetInstance ();
	//RigidBodyInfo info1;
	//info1.boxSize = LMVector3 (50, 50, 50);
	//info1.mass = 0.0f;
	//info1.origin = LMVector3 (0, -50, 0);
	//btmngr->CreateRigidBody (info1);
	//RigidBodyInfo info2;
	//info2.size = 1.0;
	//info2.mass = 1.0f;
	//info2.origin = LMVector3 (2, 10, 0);
	//btmngr->CreateRigidBody (info2);
	//exec();
	//initBullet ();
	// man->render ();
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
		//btmngr->Update ();

		i++;
	}
	audio->Clear ();

	return 0;
}
