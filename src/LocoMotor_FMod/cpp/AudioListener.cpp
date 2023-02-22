#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>

AudioListener::AudioListener (AudioManager* manager) : man(manager) {
	man->AddListener (_fIndex);
	_posRemember = new FMOD_VECTOR ();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
}

AudioListener::~AudioListener () {
}

void AudioListener::update (const float& deltaTime) {
}

void AudioListener::updateFunni (const float& deltaTime) {

	FMOD_VECTOR pos = FMOD_VECTOR ();
	pos.x = _posRemember->x + 1 * deltaTime;
	pos.y = _posRemember->y + 1 * deltaTime;
	pos.z = _posRemember->z - 1 * deltaTime;

	FMOD_VECTOR vel = FMOD_VECTOR ();
	vel.x = (pos.x - _posRemember->x) / deltaTime;
	vel.y = (pos.y - _posRemember->y) / deltaTime;
	vel.z = (pos.z - _posRemember->z) / deltaTime;

	FMOD_VECTOR frw = FMOD_VECTOR ();
	frw.x = 1;
	frw.y = 0;
	frw.z = 0;

	FMOD_VECTOR upw = FMOD_VECTOR ();
	frw.x = 0;
	frw.y = 1;
	frw.z = 0;

	man->GetSystem ()->set3DListenerAttributes (_fIndex, &pos, &vel, &frw, &upw);

	_posRemember->x = pos.x;
	_posRemember->y = pos.y;
	_posRemember->z = pos.z;
}
