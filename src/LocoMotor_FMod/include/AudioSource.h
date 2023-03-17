#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#include <unordered_map>

struct FMOD_VECTOR;
namespace FMOD {
	class Channel;
}
namespace FmodWrapper {
	class AudioManager;

	struct ChannelData {
		FMOD::Channel* channel;
		float ogFrec;
	};

	class AudioSource {
	public:

		AudioSource();
		~AudioSource();

		/// @brief Adds a sound to the manager's system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short AddSound(const unsigned int id, const char* fileName);

		/// @brief Plays a sound from this source
		/// @param id The sound to play
		/// @param loops Amount of loops the sound will do (-1 for infinite)
		/// @param loopBegin When should the sound begin its loop section (in miliseconds)
		/// @param loopEnd When should the sound end its loop section (in miliseconds)
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short PlaySound(const unsigned int id, int loops = 0, unsigned int loopBegin = 0, unsigned int loopEnd = 0xffffffff);

		unsigned short PauseS(const unsigned int id, bool pause = true);

		unsigned short PauseSource(bool pause = true);

		unsigned short StopSound(const unsigned int id);
		unsigned short StopSource();
		unsigned short SetSoundVolume(const unsigned int id, const float volume);
		unsigned short SetSourceVolume(const float volume);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short SetSoundFreq(const unsigned int id, const float freqMult);
		unsigned short SetFrequency(const float freqMult);

		/// @brief Set the position and velocity of this source. It will be applied to all sounds that are currently playing
		/// @param newPos The new position of the source
		/// @param newVel The new velocity of the source
		void SetPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel);

		void SetPositionAndVelocity(const FMOD_VECTOR& newPos, float delta);

		void Prueba();

		FmodWrapper::AudioManager* GetManager();

	private:

		FmodWrapper::AudioManager* _man;

		FMOD_VECTOR* _posRemember;

		std::unordered_map<unsigned int, ChannelData> _chMap;

		float _volumeMult;
	};
}


#endif // !AUDIOSOURCE


