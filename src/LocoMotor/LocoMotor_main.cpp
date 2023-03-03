// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"		//No se que tan legal seria hacer esto supongo el manager deberia incluir ya el listener pero habra que consultarlo nose me tengo que ir
#include "AudioSource.h"
#include "InputManager.h"
#include "CheckML.h"
#include "BulletManager.h"
#include "RenderScene.h"

int exec();
using namespace BulletWrapper;
int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	auto audio = FmodWrapper::AudioManager::Init();
	audio->AddSound(0, "Assets/engine.wav");
	auto list = FmodWrapper::AudioListener();
	auto audioSrc = FmodWrapper::AudioSource();
	//new int();
	OgreWrapper::OgreManager::Init("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::GetInstance();
	OgreWrapper::RenderScene* x = man->CreateScene("Escena");
	x->Prueba();
	man->SetActiveScene(x);
	std::cout << (x == nullptr ? "null\n" : "jiji\n");
	BulletManager::Init();
	auto btmngr = BulletManager::GetInstance();
	RigidBodyInfo info1;
	info1.boxSize = btVector3(50, 10, 50);
	info1.mass = 0.0f;
	info1.origin = btVector3(0, -50, 0);
	btmngr->CreateRigidBody(info1);
	RigidBodyInfo info2;
	info2.size = 1.0;
	info2.mass = 1.0f;
	info2.origin = btVector3(2, 10, 0);
	btmngr->CreateRigidBody(info2);

	audioSrc.PlaySound(0, -1);

	float frc = 1;

	while (true) {

		// INPUT
		if (InputManager::Get()->RegisterEvents())
			break;
		bool buttonPressed = InputManager::Get()->GetKeyDown(SDL_SCANCODE_A);

		if (InputManager::Get()->GetKey(SDL_SCANCODE_W)) {
			frc += 0.005f;
			audioSrc.SetSoundFreq(0, frc);
		}
		else if (InputManager::Get()->GetKey(SDL_SCANCODE_S)){
			frc -= 0.005f;
			audioSrc.SetSoundFreq(0, frc);
		}
		// std::cout << frc << std::endl;

		// AUDIO
		list.Prueba(.05f);
		audio->Update(0.0f);


		// RENDER
		man->Render();


		//std::cout << buttonPressed;
		// btmngr->Update();

		// JOYSTICK INPUT
		//std::cout << InputManager::Get ()->GetJoystickAxis (0, "Horizontal") << "\n";
		//std::cout << InputManager::Get ()->GetJoystickAxis (0, "Vertical") << "\n";
		//std::cout << InputManager::Get ()->GetJoystickAxis (1, "Horizontal") << "\n";
		//std::cout << InputManager::Get ()->GetJoystickAxis (1, "Vertical") << "\n";


		//i++;
	}
	FmodWrapper::AudioManager::Clear();
	OgreWrapper::OgreManager::Clear();
	InputManager::Destroy();
	return 0;
}
