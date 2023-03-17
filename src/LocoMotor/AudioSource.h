#pragma once
#ifndef LM_AUDIOSOURCE
#define LM_AUDIOSOURCE

#include "Component.h"

namespace FmodWrapper {
	class AudioSource;
}

namespace LocoMotor {
	namespace LM_Component {
		class AudioSource : public Component {

		public:
			AudioSource();
			~AudioSource();
			void Update(float dt) override;

			void Play(const unsigned short id, const int loop = 0, const unsigned int loopStart = 0, const unsigned int loopEnd = 0xffffffff);

			void PauseSound(const unsigned int id, bool pause = true);

			void Pause(bool pause = true);

			void Stop(const unsigned int id);
			void Stop();
			void SetVolume(const unsigned int id, const float volume);
			void SetVolume(const float volume);

			void SetFreq(float freqMult);
			void SetFreq(const unsigned short id, float freqMult);
		private:
			FmodWrapper::AudioSource* src;
			unsigned short lastError;
		};
	}
}

#endif // !LM_AUDIOSOURCE