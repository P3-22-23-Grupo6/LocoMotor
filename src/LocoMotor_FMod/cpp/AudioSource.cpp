#include "AudioSource.h"
#include "AudioManager.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace FmodWrapper;
using namespace FMOD;

AudioSource::AudioSource() : _man(AudioManager::GetInstance()) {
	_chMap = std::unordered_map<const char*, ChannelData>();
	_volumeMult = 1.f;
	_posRemember = new FMOD_VECTOR();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
}

AudioSource::~AudioSource() {
	delete _posRemember;
	for (auto& ch : _chMap) {
		ch.second.channel->setFrequency(1.f);
		ch.second.channel->setVolume(1.f);
		ch.second.channel->stop();
	}
}

unsigned short AudioSource::AddSound(const char* fileName) {
	return _man->AddSound(fileName);
}

unsigned short AudioSource::PlaySound(const char* fileName, int loops, unsigned int loopBegin, unsigned int loopEnd) {
	auto snd = _man->GetSound(fileName);
	if (snd == nullptr) {
	#ifdef _DEBUG
		std::cout << "Sound " << fileName << " is not added to the manager, adding it now";
	#endif // _DEBUG
		AddSound(fileName);
	}

	unsigned int len;
	snd->getLength(&len, FMOD_TIMEUNIT_MS);

	if (loopBegin >= len)
		loops = 0;
	else if (loopEnd > len)
		loopEnd = len;

	if (!loops)
		snd->setMode(FMOD_3D | FMOD_3D_WORLDRELATIVE);
	else {
		snd->setMode(FMOD_3D | FMOD_3D_WORLDRELATIVE | FMOD_LOOP_NORMAL);
		auto err = snd->setLoopPoints(std::min(loopBegin, loopEnd), FMOD_TIMEUNIT_MS, std::max(loopBegin, loopEnd), FMOD_TIMEUNIT_MS);
	#ifdef _DEBUG
		if (err != FMOD_OK) {
			std::cout << "Source error: Trying to play a loop: " << _man->GetError(err) << std::endl;
		}
	#endif
		snd->setLoopCount(std::max(-1, loops));
	}
	Channel* channel;
	auto fail = _man->PlaySoundwChannel(fileName, &channel);

	FMOD_VECTOR vel = FMOD_VECTOR(); vel.x = 0; vel.y = 0; vel.z = 0;
	if (fail != FMOD_OK)
		channel->set3DAttributes(_posRemember, &vel);
	else
		fail = channel->set3DAttributes(_posRemember, &vel);
	_chMap[fileName].channel = channel;
	float aux;
	_chMap[fileName].channel->getFrequency(&aux);
	_chMap[fileName].ogFrec = aux;
	_chMap[fileName].channel->setVolume(_volumeMult);

	channel->setPaused(false);
	return fail;
}

unsigned short FmodWrapper::AudioSource::PauseS(const char* fileName, bool pause) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cout << "Sound " << fileName << " is not currently playing on this AudioSource, from PauseSound()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setPaused(pause);
}

unsigned short FmodWrapper::AudioSource::PauseSource(bool pause) {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		auto aux = chan.second.channel->setPaused(pause);
		if (aux > res) {
			res = aux;
		}
	}
	return res;
}

unsigned short FmodWrapper::AudioSource::StopSound(const char* fileName) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cout << "Sound '" << fileName << "' is not currently playing on this AudioSource, from Stop()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->stop();
}

unsigned short FmodWrapper::AudioSource::StopSource() {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		auto aux = chan.second.channel->stop();
		if (aux > res) {
			res = aux;
		}
	}
	return res;
}

unsigned short FmodWrapper::AudioSource::SetSoundVolume(const char* fileName, const float volume) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cout << "Sound '" << fileName << "' is not currently playing on this AudioSource, from SetVolume()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setVolume(volume);
}

unsigned short FmodWrapper::AudioSource::SetSourceVolume(const float volume) {
	unsigned short res = 0;
	for (auto& chan : _chMap) {
		auto aux = chan.second.channel->setVolume(volume);
		if (aux > res) {
			res = aux;
		}
	}
	_volumeMult = volume;
	return res;
}

unsigned short AudioSource::SetSoundFreq(const char* fileName, const float freqMult) {
	if (!_chMap[fileName].channel) {
	#ifdef _DEBUG
		std::cout << "Sound " << fileName << " is not currently playing on this AudioSource, from SetSoundFreq()";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[fileName].channel->setFrequency(std::max(0.f, _chMap[fileName].ogFrec * freqMult));
}

unsigned short FmodWrapper::AudioSource::SetFrequency(const float freqMult) {
	return 0;
}

void AudioSource::SetPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel) {
	for (auto& ch : _chMap) {
		bool is;
		ch.second.channel->isPlaying(&is);
		if (is) {
			ch.second.channel->set3DAttributes(&newPos, &newVel);
		}
		else {
			ch.second.channel->setFrequency(ch.second.ogFrec);
			ch.second.channel->setVolume(1.f);
			ch.second.channel->stop();
			ch.second.channel = nullptr;
			_chMap.erase(ch.first);
		}
	}

	_posRemember->x = newPos.x;
	_posRemember->y = newPos.y;
	_posRemember->z = newPos.z;
}

void FmodWrapper::AudioSource::SetPositionAndVelocity(const FMOD_VECTOR& newPos, float delta) {
	FMOD_VECTOR vel = FMOD_VECTOR(); 
	vel.x = (newPos.x - _posRemember->x) / delta;
	vel.y = (newPos.y - _posRemember->y) / delta;
	vel.z = (newPos.z - _posRemember->z) / delta;

	SetPositionAndVelocity(newPos, vel);
}

void FmodWrapper::AudioSource::Prueba() {
	/*FMOD_VECTOR aux = FMOD_VECTOR(); aux.x = _posRemember->x - 0.0001f; aux.y = _posRemember->y; aux.z = _posRemember->z;
	SetPositionAndVelocity(aux, FMOD_VECTOR());*/
}

FmodWrapper::AudioManager* FmodWrapper::AudioSource::GetManager() {
	return _man;
}
