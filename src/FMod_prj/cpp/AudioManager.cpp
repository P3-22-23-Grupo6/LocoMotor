#include "../include/AudioManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <fmod_errors.h>

/// <summary>
/// Constructor is set to private, use the 'Get' method for access to the instance of this object
/// </summary>
AudioManager::AudioManager()
{
	System_Create(&_sys);
	_sys->init(8, FMOD_INIT_NORMAL, 0);
	_sys->createChannelGroup(0, &_main);
}

AudioManager::~AudioManager()
{
	for (auto snd : _soundLib)
	{
		snd.second->release();
		delete snd.second;
	}
	_main->release();
	delete _main;
	_sys->release();
	delete _sys;
}

/// <summary>
/// Static getter for access to the instance, when called for the first time, it will create the instance, and from then on it will return the previously created instance
/// </summary>
/// <returns>
/// The reference to the instance of the AudioManager
/// </returns>
AudioManager* AudioManager::Get()
{
	static AudioManager* inst = new AudioManager();
	return inst;
}

/// <summary>
/// Adds a sound to the system, for later use
/// </summary>
/// <param name="name">Name that will be used to refer to this sound upon being created</param>
/// <param name="fileName">File to get the sound from</param>
/// <returns>A number that by passing it to GetError(uint16_t) you can get more info if there was an error</returns>
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

/// <summary>
/// Plays an already added sound
/// </summary>
/// <param name="name">Name of the sound to play</param>
/// <returns>A number that by passing it to GetError(uint16_t) you can get more info if there was an error</returns>
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

const char* AudioManager::GetError(uint16_t& errorCode)
{
	return FMOD_ErrorString((FMOD_RESULT)errorCode);
}
