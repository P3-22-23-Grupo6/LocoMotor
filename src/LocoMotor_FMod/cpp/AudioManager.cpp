#include "AudioManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <fmod.hpp>
#include <fmod_errors.h>
using namespace FMOD;

AudioManager::AudioManager () {
	System_Create (&_sys);
	_sys->init (32, FMOD_INIT_NORMAL, 0);
	_sys->createChannelGroup (0, &_main);

	_sys->set3DNumListeners (0);
	_sys->set3DSettings (1.f, 1.f, 1.f);

	_soundLib = std::unordered_map<uint32_t, FMOD::Sound*> ();
}

AudioManager::~AudioManager () {
	for (auto snd : _soundLib) {
		snd.second->release ();
		delete snd.second;
	}
	_main->release ();
	delete _main;
	_sys->close ();
	_sys->release ();
	delete _sys;
}

AudioManager* AudioManager::Get () {
	static AudioManager* inst = new AudioManager ();
	return inst;
}

uint16_t AudioManager::AddSound (const uint32_t id, const char* fileName) {
	if (_soundLib[id] != nullptr) {
		_soundLib[id]->release ();
	}

#ifndef _DEBUG
	return _sys->createSound (fileName, FMOD_DEFAULT, nullptr, &_soundLib[id]);
#endif // _DEBUG

#ifdef _DEBUG
	auto err = _sys->createSound (fileName, FMOD_3D, nullptr, &_soundLib[id]);

	if (err != 0) {
		std::cout << "AUDIO: File '" << fileName << "' caused fmod exception: " << FMOD_ErrorString (err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

uint16_t AudioManager::PlaySound (const uint32_t id) {
#ifndef _DEBUG
	return _sys->playSound (_soundLib[id], _main, false, NULL);
#endif // _DEBUG

#ifdef _DEBUG
	Channel* ch;
	auto err = _sys->playSound (_soundLib[id], _main, true, &ch);

	FMOD_VECTOR pos = FMOD_VECTOR(); FMOD_VECTOR vel = FMOD_VECTOR ();
	pos.x = 30; pos.y = 3; pos.z = 3; vel.x = -8; vel.y = 0; vel.z = 0;
	ch->set3DAttributes (&pos, &vel);

	ch->setPaused (false);

	if (err != 0) {
		std::cout << "AUDIO: Trying to play sound '" << id << "' caused fmod exception: " << FMOD_ErrorString (err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

uint16_t AudioManager::AddListener (int& index) {
	_sys->get3DNumListeners (&index);
	return _sys->set3DNumListeners (index + 1);
}

FMOD::System* AudioManager::GetSystem () {
	return _sys;
}

const char* AudioManager::GetError (uint16_t& errorCode) {
	return FMOD_ErrorString ((FMOD_RESULT) errorCode);
}
