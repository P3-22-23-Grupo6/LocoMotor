#pragma once
#ifndef LM_AUDIOLISTENER
#define LM_AUDIOLISTENER

#include "Component.h"

namespace FmodWrapper {
	class AudioListener;
}
class LMVector3;

namespace LocoMotor {
	namespace LM_Component {
		class AudioListener : public Component {

		public:
			AudioListener();
			~AudioListener();
			void Start() override;
			void Update(float dt) override;
		private:
			FmodWrapper::AudioListener* _list;
			LMVector3* _lastPos;
		};
	}
}

#endif // !LM_AUDIOLISTENER