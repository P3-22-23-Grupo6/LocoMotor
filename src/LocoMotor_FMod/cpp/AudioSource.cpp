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
	_chMap = std::unordered_map<unsigned int, ChannelData>();
	_posRemember = new FMOD_VECTOR();
	_posRemember->x = 0;
	_posRemember->y = 0;
	_posRemember->z = 0;
}

AudioSource::~AudioSource() {
	delete _posRemember;
	for (auto& ch : _chMap) {
		ch.second.channel->setFrequency(1);
		ch.second.channel->stop();
	}
}

unsigned short AudioSource::AddSound(const unsigned int id, const char* fileName) {
	return _man->AddSound(id, fileName);
}

unsigned short AudioSource::PlaySound(const unsigned int id, int loops, unsigned int loopBegin, unsigned int loopEnd) {
	auto snd = _man->GetSound(id);
	if (snd == nullptr) {
	#ifdef _DEBUG
		std::cout << "Sound " << id << " is not currently added to the manager";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
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
	auto fail = _man->PlaySoundwChannel(id, &channel);

	FMOD_VECTOR vel = FMOD_VECTOR(); vel.x = 0; vel.y = 0; vel.z = 0;
	if (fail != FMOD_OK)
		channel->set3DAttributes(_posRemember, &vel);
	else
		fail = channel->set3DAttributes(_posRemember, &vel);
	_chMap[id].channel = channel;
	float aux;
	_chMap[id].channel->getFrequency(&aux);
	_chMap[id].ogFrec = aux;

	channel->setPaused(false);
	return fail;
}

unsigned short AudioSource::SetSoundFreq(const unsigned int id, const float freqMult) {
	if (!_chMap[id].channel) {
	#ifdef _DEBUG
		std::cout << "Sound " << id << " is not currently playing on this AudioSource";
	#endif // _DEBUG
		return FMOD_ERR_INVALID_PARAM;
	}
	return _chMap[id].channel->setFrequency(std::max(0.f, _chMap[id].ogFrec * freqMult));
}

void AudioSource::SetPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel) {
	for (auto& ch : _chMap) {
		bool is;
		ch.second.channel->isPlaying(&is);
		if (is) {
			ch.second.channel->set3DAttributes(&newPos, &newVel);
		}
		else {
			float aux;
			ch.second.channel->getFrequency(&aux);
			ch.second.ogFrec = aux;
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
