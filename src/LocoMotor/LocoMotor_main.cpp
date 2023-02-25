// MiMotor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OgreManager.h"
#include "RenderScene.h"
#include "AudioManager.h"
#include <OgreRenderWindow.h>
#include <SDL_events.h>

int exec ();
int initBullet ();

int main () {
	/*AudioManager::Get ()->AddSound ("si", "si.wav");
	AudioManager::Get ()->PlaySound ("si");*/

	OgreWrapper::OgreManager::Init ("Prueba");
	OgreWrapper::OgreManager* man = OgreWrapper::OgreManager::GetInstance ();
	OgreWrapper::RenderScene* x = man->CreateScene ("Escena");

	x->Prueba ();
	man->SetActiveScene (x);
	//std::cout << (x == nullptr ? "null\n" : "jiji\n");
	//exec();
	//initBullet ();
	// exec();
	char basura;
	while(true){
		man->Render ();

		SDL_Event evt;
		
		SDL_PollEvent (&evt);
		if (evt.type == SDL_QUIT) {
			break;
		}
	}
	
	return 0;
}
