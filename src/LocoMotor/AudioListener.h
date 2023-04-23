#pragma once
#ifndef LM_AUDIOLISTENER
#define LM_AUDIOLISTENER
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace FmodWrapper {
	class AudioListener;
}
class LMVector3;

namespace LocoMotor {
	class MOTOR_API AudioListener : public Component {

	public:
		const static std::string name;
		static std::string GetName() {
			return "AudioListener";
		};
		AudioListener();
		~AudioListener();

		/// @brief Sets the initial position of the listener to the gameobject's
		void Start() override;
		void InitComponent() override;
		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
	private:
		FmodWrapper::AudioListener* _list;
		LMVector3* _lastPos;
	};
};
#endif // !LM_AUDIOLISTENER