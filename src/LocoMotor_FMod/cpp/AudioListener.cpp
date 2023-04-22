#include "AudioListener.h"
#include "AudioManager.h"
#include <fmod_common.h>
#include <fmod.hpp>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

FmodWrapper::AudioListener::AudioListener() : _man(AudioManager::GetInstance()) {
	_thisIT = _man->AddListener(this, _fIndex);
}

FmodWrapper::AudioListener::~AudioListener() {
	_man->RemoveListener(_thisIT, _fIndex);
}

unsigned short FmodWrapper::AudioListener::SetTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up) {

#ifdef _DEBUG
	auto err = _man->GetSystem()->set3DListenerAttributes((int) _fIndex, &newPos, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cout << "Listener error: " << _man->GetError(err) << std::endl;
	}
	return err;
#else
	return _man->GetSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
#endif // _DEBUG
}

unsigned short FmodWrapper::AudioListener::ChangeIndex(int index)
{
	FMOD_VECTOR newPos; FMOD_VECTOR newVel; FMOD_VECTOR forward; FMOD_VECTOR up;

	auto err = _man->GetSystem()->get3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);

	if (err == 0)
		err = _man->GetSystem()->set3DListenerAttributes(index, &newPos, &newVel, &forward, &up);

	_fIndex = (size_t)index;

	return err;
}
