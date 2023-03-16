#pragma once
#ifndef LM_AUDIOSOURCE
#define LM_AUDIOSOURCE

#include "Component.h"

namespace FmodWrapper {
	class AudioSource;
}

namespace LocoMotor {
	namespace Component {
		class AudioSource : public Component {

		public:
			AudioSource();
			void Update(float dt) override;

			void PlaySound(const unsigned short id, const int loop = 0, const unsigned int loopStart = 0, const unsigned int loopEnd = 0xffffffff);
		private:

			FmodWrapper::AudioSource* src;
		};
	}
}

#endif // !LM_AUDIOSOURCE

