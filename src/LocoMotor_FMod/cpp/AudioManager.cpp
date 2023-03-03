#include "AudioManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <fmod.hpp>
#include <fmod_errors.h>

using namespace FMOD;
using namespace FmodWrapper;

AudioManager* Singleton<AudioManager>::_instance = nullptr;

AudioManager::AudioManager() {
	System_Create(&_sys);
	_sys->init(32, FMOD_INIT_NORMAL, 0);
	_sys->createChannelGroup(0, &_main);

	_sys->set3DSettings(1.f, 1.f, 1.f);

	_soundLib = std::unordered_map<uint32_t, FMOD::Sound*>();
}

AudioManager::~AudioManager() {
	for (auto snd : _soundLib) {
		snd.second->release();
		//delete snd.second;
	}
	_main->release();
	//delete _main;
	_sys->close();
	_sys->release();
	//delete _sys;
}

uint16_t AudioManager::Update(float deltaTime) {
	return _sys->update();
}

uint16_t AudioManager::AddSound(const uint32_t name, const char* fileName, bool ui) {
	if (_soundLib[name] != nullptr) {
		_soundLib[name]->release();
		_soundLib[name] = nullptr;
	}

#ifndef _DEBUG
	if (ui)
		return _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[name]);
	else
		return _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[name]);
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err;
	if (ui)
		err = _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[name]);
	else
		err = _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[name]);

	if (err != 0) {
		std::cout << "AUDIO: File '" << fileName << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

uint16_t AudioManager::PlaySound(const uint32_t name) {

	Channel* ch;
	auto err = PlaySoundwChannel(name, &ch);
	ch->setPaused(false);
	return err;
}

uint16_t AudioManager::PlaySoundwChannel(const uint32_t name, Channel** channel) {
#ifndef _DEBUG
	auto err = _sys->playSound(_soundLib[name], _main, true, channel);

	return err;
#endif // _DEBUG

#ifdef _DEBUG
	auto err = _sys->playSound(_soundLib[name], _main, true, channel);

	if (err != 0) {
		std::cout << "AUDIO: Trying to play sound '" << name << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

Sound* AudioManager::GetSound(const uint32_t id) {
	return _soundLib[id];
}

uint16_t AudioManager::AddListener(int& index) {
	static bool first = true;
	if (first) {
		first = false;
		index = 0;
		return 0;
	}
	else {
		_sys->get3DNumListeners(&index);
		return _sys->set3DNumListeners(index + 1);
	}
}

System* AudioManager::GetSystem() const {
	return _sys;
}

const char* AudioManager::GetError(const uint16_t& errorCode) {
	return FMOD_ErrorString((FMOD_RESULT) errorCode);
}
