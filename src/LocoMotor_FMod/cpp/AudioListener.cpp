#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

AudioListener::AudioListener (AudioManager* manager) : man (manager) {
	man->AddListener (_fIndex);
	_posRemember = new FMOD_VECTOR ();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
	_elapsedTime = 0;
}

AudioListener::~AudioListener () {
}

void AudioListener::update (const float& deltaTime) {
}

void AudioListener::updateFunni (const float& deltaTime) {

	_elapsedTime += deltaTime;

	FMOD_VECTOR pos = FMOD_VECTOR ();
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	FMOD_VECTOR vel = FMOD_VECTOR ();
	vel.x = (pos.x - _posRemember->x) / deltaTime;
	vel.y = (pos.y - _posRemember->y) / deltaTime;
	vel.z = (pos.z - _posRemember->z) / deltaTime;

	FMOD_VECTOR frw = FMOD_VECTOR ();
	frw.x = cos (_elapsedTime);
	frw.y = 0;
	frw.z = sin (_elapsedTime);

	FMOD_VECTOR upw = FMOD_VECTOR ();
	upw.x = 0;
	upw.y = 1;
	upw.z = 0;

	std::cout << man->GetError (man->GetSystem ()->set3DListenerAttributes (0, &pos, &vel, &frw, &upw)) << std::endl;

	_posRemember->x = pos.x;
	_posRemember->y = pos.y;
	_posRemember->z = pos.z;

}
