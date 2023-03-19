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

			/// @brief Sets the initial position of the listener to the gameobject's
			void Start() override;

			/// @brief Updates the listener's world attributes to be the same as the gameobject's
			/// @param dt DeltaTime used to calculate the velocity
			void Update(float dt) override;
		private:
			FmodWrapper::AudioListener* _list;
			LMVector3* _lastPos;
		};
	}
}

#endif // !LM_AUDIOLISTENER