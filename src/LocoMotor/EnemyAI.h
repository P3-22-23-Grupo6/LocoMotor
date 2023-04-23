#pragma once
#include "Component.h"

class LMVector3;

namespace LocoMotor {
	class GameObject;
	class Spline;
	class EnemyAI : public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "EnemyAI";
		};
		EnemyAI();
		~EnemyAI();
		/// @brief Sets the initial position of the listener to the gameobject's
		void Start(LocoMotor::Spline* splineToFollow, float sep);

		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
	private:
		//OgreWrapper::RenderScene* _renderScn;
		LMVector3* currentNode;
		Spline* mySpline;
		GameObject* myGbj;
		float timeStep, lastTimeStep;
		//STATS
		float enemySpeed;
		float enemyMaxAcc;
		float startSeparation;
	};
}