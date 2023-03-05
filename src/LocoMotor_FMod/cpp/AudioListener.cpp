#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

FmodWrapper::AudioListener::AudioListener() : _man(AudioManager::GetInstance()) {
	_man->AddListener(_fIndex);
	_posRemember = new FMOD_VECTOR();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
	_elapsedTime = 0;

}

FmodWrapper::AudioListener::~AudioListener() {
	delete _posRemember;
}

unsigned short FmodWrapper::AudioListener::SetTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up) {

#ifdef _DEBUG
	auto err = _man->GetSystem()->set3DListenerAttributes(_fIndex, &newPos, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cout << "Listener error: " << _man->GetError(err) << std::endl;
	}
	return err;
#else
	return _man->GetSystem()->set3DListenerAttributes(_fIndex, &newPos, &newVel, &forward, &up);
#endif // _DEBUG
}

void FmodWrapper::AudioListener::Prueba(const float& deltaTime) {

	_elapsedTime += deltaTime;

	FMOD_VECTOR pos = FMOD_VECTOR();
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	FMOD_VECTOR vel = FMOD_VECTOR();

	//vel.x = (pos.x - _posRemember->x) / deltaTime;
	//vel.y = (pos.y - _posRemember->y) / deltaTime;
	//vel.z = (pos.z - _posRemember->z) / deltaTime;

	vel.x = 0;
	vel.y = 0;
	vel.z = 0;

	FMOD_VECTOR frw = FMOD_VECTOR();
	frw.x = cos(_elapsedTime);
	frw.y = 0;
	frw.z = sin(_elapsedTime);

	FMOD_VECTOR upw = FMOD_VECTOR();
	upw.x = 0;
	upw.y = 1;
	upw.z = 0;

	_posRemember->x = pos.x;
	_posRemember->y = pos.y;
	_posRemember->z = pos.z;

#ifdef _DEBUG
	auto err = _man->GetSystem()->set3DListenerAttributes(_fIndex, &pos, &vel, &frw, &upw);
	if (err != FMOD_OK) {
		std::cout << "Listener error: " << _man->GetError(err) << std::endl;
	}
#else
	_man->GetSystem()->set3DListenerAttributes(_fIndex, &pos, &vel, &frw, &upw);
#endif // _DEBUG

}
//
//void AudioListener::Update (const unsigned int& deltaTime) {
//	float dT = (float) deltaTime / 1000.f;
//	Update (dT);
//}
//
//void AudioListener::UpdateFunni (const unsigned int& deltaTime) {
//	float dT = (float) deltaTime / 1000.f;
//	UpdateFunni (dT);
//}
