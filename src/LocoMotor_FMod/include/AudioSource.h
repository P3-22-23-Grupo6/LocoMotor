#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#include <unordered_map>

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
struct FMOD_VECTOR;
namespace FMOD {
	class Channel;
}
namespace FmodWrapper {
	class AudioManager;

	class AudioSource {
	public:

		AudioSource();
		~AudioSource();

		/// @brief Adds a sound to the manager's system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		/// @return A number that by passing it to AudioManager::GetError(uint16_t) you can get more info if there was an error
		uint16_t AddSound(const uint32_t id, const char* fileName);

		/// @brief Plays a sound from this source
		/// @param id The sound to play
		/// @param loops Amount of loops the sound will do (-1 for infinite)
		/// @param loopBegin When should the sound begin its loop section (in miliseconds)
		/// @param loopEnd When should the sound end its loop section (in miliseconds)
		/// @return A number that by passing it to AudioManager::GetError(uint16_t) you can get more info if there was an error
		uint16_t PlaySound(const uint32_t id, int loops = 0, uint32_t loopBegin = 0, uint32_t loopEnd = 0xffffffff);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		/// @return A number that by passing it to AudioManager::GetError(uint16_t) you can get more info if there was an error
		uint16_t SetSoundFreq(const uint32_t id, const float freqMult);

		/// @brief Set the position and velocity of this source. It will be applied to all sounds that are currently playing
		/// @param newPos The new position of the source
		/// @param newVel The new velocity of the source
		void SetPositionAndVelocity(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel);

		void Prueba();

	private:

		FmodWrapper::AudioManager* _man;

		FMOD_VECTOR* _posRemember;

		std::unordered_map<uint32_t, FMOD::Channel*> _chMap;


	};
}


#endif // !AUDIOSOURCE


