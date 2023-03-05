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

	class AudioSource;
	class AudioListener;

	class AudioManager : public Singleton<FmodWrapper::AudioManager> {

		friend Singleton<FmodWrapper::AudioManager>;
		friend AudioSource;
		friend AudioListener;

	public:
		~AudioManager();

		/// @brief Updates the Fmod API to change channel output depending on positions and velocity
		/// @param deltaTime Bruh
		/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
		unsigned short Update(float deltaTime);

		/// @brief Adds a sound to the system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
		unsigned short AddSound(const unsigned int id, const char* fileName, bool ui = false);

		/// @brief Plays an already added sound
		/// @param Name of the sound to play
		/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
		unsigned short PlaySound(const unsigned int id);

		/// @brief Adds a listener to Fmod
		/// @param index The index of the newly created listener
		/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
		unsigned short AddListener(int& index);

		/// @brief Gets the FMOD::System object from this manager
		/// @return The System in question
		FMOD::System* GetSystem() const;

		/// @brief Get the fmod error corresponding to the param passed
		/// @param errorCode Param to get the Fmod error corresponding to it
		/// @return The Fmod error message
		const char* GetError(const unsigned short& errorCode);

	private:

		FMOD::System* _sys = nullptr;
		FMOD::ChannelGroup* _main = nullptr;

		std::unordered_map<unsigned int, FMOD::Sound*> _soundLib;

		/// @brief Constructor is set to private, use the 'Get' method for access to the instance of this object
		AudioManager();

		/// @brief Plays an already added sound, but gives access to the channel its being played
		/// @param Name of the sound to play
		/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
		unsigned short PlaySoundwChannel(const unsigned int name, FMOD::Channel** channel);

		FMOD::Sound* GetSound(const unsigned int id);

	};
}

#endif // !AUDIOMANAGER