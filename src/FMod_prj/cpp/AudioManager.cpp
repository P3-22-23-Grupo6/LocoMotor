#include "../include/AudioManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <fmod_errors.h>


AudioManager::AudioManager()
{
	System_Create(&_sys);
	_sys->init(8, FMOD_INIT_NORMAL, 0);
	_sys->createChannelGroup(0, &_main);
}

AudioManager::~AudioManager()
{
}

AudioManager* AudioManager::Get()
{
	static AudioManager* inst = new AudioManager();
	return inst;
}

uint16_t AudioManager::AddSound(const char* name, const char* fileName)
{
	if (_soundLib[name] != nullptr) {
		_soundLib[name]->release();
	}

#ifndef _DEBUG
	return _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[name]);    //18 == FMOD_ERR_FILE_NOTFOUND
#endif // _DEBUG

#ifdef _DEBUG
	auto err = _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[name]);
	if (err != 0) {
		std::cout << "AUDIO: File '" << fileName << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}

uint16_t AudioManager::PlaySound(const char* name)
{
#ifndef _DEBUG
	return _sys->playSound(_soundLib[name], _main, false, NULL);    //18 == FMOD_ERR_FILE_NOTFOUND
#endif // _DEBUG

#ifdef _DEBUG
	auto err = _sys->playSound(_soundLib[name], _main, false, NULL);
	if (err != 0) {
		std::cout << "AUDIO: Trying to play sound '" << name << "' caused fmod exception: " << FMOD_ErrorString(err) << std::endl;
	}
	return err;
#endif // _DEBUG
}
