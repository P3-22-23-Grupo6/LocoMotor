#pragma once
#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#include <unordered_map>
#include "Singleton.h"

namespace FMOD {
	class System;
	class ChannelGroup;
	class Channel;
	class Sound;
}

namespace FmodWrapper {

	class AudioManager : public Singleton<FmodWrapper::AudioManager> {

		friend Singleton<FmodWrapper::AudioManager>;

	public:
		~AudioManager ();

		/// @brief Updates the Fmod API to change channel output depending on positions and velocity
		/// @param deltaTime Bruh
		/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
		uint16_t Update (float deltaTime);

		/// @brief Adds a sound to the system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
		uint16_t AddSound (const uint32_t id, const char* fileName, bool ui = false);

		/// @brief Plays an already added sound
		/// @param Name of the sound to play
		/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
		uint16_t PlaySound (const uint32_t id);

		/// @brief Adds a listener to Fmod
		/// @param index The index of the newly created listener
		/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
		uint16_t AddListener (int& index);

		/// @brief Gets the FMOD::System object from this manager
		/// @return The System in question
		FMOD::System* GetSystem ();

		/// @brief Get the fmod error corresponding to the param passed
		/// @param errorCode Param to get the Fmod error corresponding to it
		/// @return The Fmod error message
		const char* GetError (const uint16_t& errorCode);

	private:

		FMOD::System* _sys = nullptr;
		FMOD::ChannelGroup* _main = nullptr;

		std::unordered_map<uint32_t, FMOD::Sound*> _soundLib;

		/// @brief Constructor is set to private, use the 'Get' method for access to the instance of this object
		AudioManager ();

		/// @brief Plays an already added sound
		/// @param Name of the sound to play
		/// @return A number that by passing it to GetError(uint16_t) you can get more info if there was an error
		uint16_t PlaySoundwChannel (const uint32_t name, FMOD::Channel** channel);

	};
}

#endif // !AUDIOMANAGER