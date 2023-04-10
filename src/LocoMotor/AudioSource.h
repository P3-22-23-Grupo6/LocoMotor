#pragma once
#ifndef LM_AUDIOSOURCE
#define LM_AUDIOSOURCE

#include "Component.h"

namespace FmodWrapper {
	class AudioSource;
}

namespace LocoMotor {
		class AudioSource : public Component {

		public:
			const static std::string name;
			static std::string GetName() {
				return "AudioSource";
			};

			AudioSource();
			~AudioSource();

			/// @brief Updates the source's position and velocity in the world
			/// @param dt DeltaTime used to calculate the velocity by comparing last position
			void Update(const float dt) override;


			/// @brief Plays a sound loaded in the system
			/// @param fileName the file where the sound is, it will load the first time it plays and stay loaded until the game closes
			/// @param loop amount of loops the sound will do (-1 for infinite)
			/// @param loopStart The begining of the loop section (in miliseconds)
			/// @param loopEnd The end of the loop section (in miliseconds)
			void Play(const char* fileName, const int loop = 0, const unsigned int loopStart = 0, const unsigned int loopEnd = 0xffffffff);

			/// @brief Pauses a specific sound that is being played
			/// @param id The sound to pause
			/// @param pause Bool to pause or unpause
			void PauseSound(const char* fileName, const bool pause = true);

			/// @brief Pause all sounds that are currently playing on the source 
			/// (will not pause sounds that start playing after this is called)
			/// @param pause Bool to pause or unpause
			void Pause(const bool pause = true);

			/// @brief Stops playing a specific sound
			/// @param id Sound to stop
			void Stop(const char* fileName);

			/// @brief Stops all sounds from this source
			void Stop();


			/// @brief Set the volume multiplier for a sound that is being played
			/// @param id The sound to apply the volume change to
			/// @param volume float in the range of 0.f (no volume) - 1.f (max volume)
			void SetVolume(const char* fileName, const float volume);

			/// @brief Set the volume multiplier for all sounds that play on this source
			/// @param volume float in the range of 0.f (no volume) - 1.f (max volume)
			void SetVolume(const float volume);

			/// @brief Set the frequency multiplier for a sound that is being played
			/// @param id The sound to apply the changes to
			/// @param freqMult by how much should the original frequency of each sound be multiplied by
			void SetFreq(const char* fileName, float freqMult);

			/// @brief Set the frequency multiplier for all sounds that play on this source
			/// @param freqMult by how much should the original frequency of each sound be multiplied by
			void SetFreq(const float freqMult);
		private:
			FmodWrapper::AudioSource* _src;
			unsigned short _lastError;
		};
}

#endif // !LM_AUDIOSOURCE