// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "AudioManager.h"
#include "AudioListener.h"		//No se que tan legal seria hacer esto supongo el manager deberia incluir ya el listener pero habra que consultarlo nose me tengo que ir
#include "InputManager.h"

int exec ();
int initBullet ();

int main () {
	AudioManager::Get ()->AddSound (0, "si.wav");
	auto list = AudioListener (AudioManager::Get ());
	list.UpdateFunni (5.f);
	AudioManager::Get ()->Update (0.0f);
	AudioManager::Get ()->PlaySound (0);


	OgreWrapper::OgreManager::init ("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::getInstance ();
	man->createScene ("Escena");
	man->createScene ("Escena2");

	OgreWrapper::Scene* x = man->getScene ("Escenah");
	std::cout << (x == nullptr ? "null\n" : "jiji\n");
	//exec();
	initBullet ();
	man->render ();

	char basura;
	std::cin >> basura;
	return 0;
}
