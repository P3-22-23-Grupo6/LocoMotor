#pragma once
#include "Component.h"

class LMVector3;

namespace LocoMotor {
	class GameObject;
	class Boost : public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "Boost";
		};
		Boost();
		~Boost();
		/// @brief Sets the initial position of the listener to the gameobject's
		void Start(float thrust);

		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;

		void OnCollisionEnter(GameObject* other) override;
		//void OnCollisionStay(GameObject* other) override;
		//void OnCollisionExit(GameObject* other) override;
	private:
		GameObject* myGbj;
		//STATS
		float boostThrust;
	};
}