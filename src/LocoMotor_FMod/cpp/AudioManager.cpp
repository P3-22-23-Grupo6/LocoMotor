#include "AudioManager.h"
#include "AudioListener.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <fmod.hpp>
#include <fmod_errors.h>

using namespace FMOD;
using namespace FmodWrapper;

AudioManager* Singleton<AudioManager>::_instance = nullptr;

AudioManager::AudioManager() : AudioManager(32){ }

AudioManager::AudioManager(int numChannels) {
	System_Create(&_sys);
	_sys->init(numChannels, FMOD_INIT_NORMAL, 0);
	_sys->createChannelGroup(0, &_main);

	float vol;
	_main->getVolume(&vol);
	_sys->set3DSettings(15.f, 30.f, 1.f);

	_soundLib = std::unordered_map<const char*, FMOD::Sound*>();
}

AudioManager::~AudioManager() {
	for (auto& snd : _soundLib) {
		snd.second->release();
		//delete snd.second;
	}
	_main->release();
	//delete _main;
	_sys->close();
	_sys->release();
	//delete _sys;
}

unsigned short AudioManager::Update(float deltaTime) {
	return _sys->update();
}

unsigned short AudioManager::AddSound(const char* fileName, bool ui) {
	if (_soundLib[fileName] != nullptr) {
		if (ui)
			_soundLib[fileName]->setMode(FMOD_DEFAULT);
		else
			_soundLib[fileName]->setMode(FMOD_3D_WORLDRELATIVE);
		return 0;
	}

#ifndef _DEBUG
	if (ui)
		return _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		return _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err;
	if (ui)
		err = _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		err = _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);

	if (err != 0) {
		std::cout << "AUDIO: File '" << fileName << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

unsigned short AudioManager::PlaySound(const char* name) {

	Channel* ch;
	auto err = PlaySoundwChannel(name, &ch);
	ch->setPaused(false);
	return err;
}

unsigned short AudioManager::PlaySoundwChannel(const char* name, Channel** channel) {
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

Sound* AudioManager::GetSound(const char* id) {
	return _soundLib[id] ? _soundLib[id] : nullptr;
}

std::list<AudioListener*>::iterator AudioManager::AddListener(AudioListener* curr, size_t& index) {
	index = _listeners.size();
	_listeners.push_back(curr);

	_sys->set3DNumListeners((int)_listeners.size());

	std::list<AudioListener*>::iterator it = _listeners.end();
	it--;
	return it;
}

unsigned short FmodWrapper::AudioManager::RemoveListener(std::list<AudioListener*>::iterator listenerIt, size_t indexToRemove) {
	auto it = _listeners.erase(listenerIt);
	int nIndex = (int)indexToRemove;

	unsigned short err = 0;

	while (it != _listeners.end()) {
		err = (*it)->ChangeIndex(nIndex);

	#ifdef _DEBUG
		if (err != 0) {
			std::cout << "AUDIO: Trying to update listeners while removing number '" << indexToRemove << "' caused fmod exception: " << FMOD_ErrorString((FMOD_RESULT)err) << std::endl;
		}
	#endif // _DEBUG

		nIndex++;
	}
	_sys->set3DNumListeners((int)_listeners.size());
	return err;
}

System* AudioManager::GetSystem() const {
	return _sys;
}

const char* AudioManager::GetError(const unsigned short& errorCode) {
	return FMOD_ErrorString((FMOD_RESULT) errorCode);
}
