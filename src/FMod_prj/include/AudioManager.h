#pragma once
#ifndef AUDIOMANAGER
#define AUDIOMANAGER


#include <unordered_map>
#include <fmod.hpp>
using namespace FMOD;

class AudioManager {

	System* _sys = nullptr;
	ChannelGroup* _main = nullptr;

	std::unordered_map<const char*, Sound*> _soundLib = std::unordered_map<const char*, Sound*>();

	AudioManager();
	~AudioManager();

public:

	static AudioManager* Get();

	uint16_t AddSound(const char* name, const char* fileName);

	uint16_t PlaySound(const char* name);

	const char* GetError(uint16_t& errorCode);
};


#endif // !AUDIOMANAGER

