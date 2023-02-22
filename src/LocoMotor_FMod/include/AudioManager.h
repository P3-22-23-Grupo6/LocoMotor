#pragma once
#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include <unordered_map>

namespace FMOD {
	class System;
	class ChannelGroup;
	class Sound;
}

class AudioManager {
public:

	/// @brief Static getter for access to the instance, when called for the first time, it will create the instance, and from then on it will return the previously created instance
	/// @return The reference to the instance of the AudioManager
	static AudioManager* Get ();

	/// @brief Adds a sound to the system, for later use
	/// @param Name that will be used to refer to this sound upon being created
	/// @param File to get the sound from
	/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
	uint16_t AddSound (const uint32_t id, const char* fileName);

	/// @brief Plays an already added sound
	/// @param Name of the sound to play
	/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
	uint16_t PlaySound (const uint32_t id);

	/// @brief Adds a listener to Fmod
	/// @param index The index of the newly created listener
	/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
	uint16_t AddListener (int& index);

	FMOD::System* GetSystem ();

	/// @brief Get the fmod error corresponding to the param passed
	/// @param errorCode Param to get the Fmod error corresponding to it
	/// @return The Fmod error message
	const char* GetError (uint16_t& errorCode);

private:

	FMOD::System* _sys = nullptr;
	FMOD::ChannelGroup* _main = nullptr;

	std::unordered_map<uint32_t, FMOD::Sound*> _soundLib;

	/// @brief Constructor is set to private, use the 'Get' method for access to the instance of this object
	AudioManager ();
	~AudioManager ();

};


#endif // !AUDIOMANAGER

