#pragma once
#include "Component.h"

namespace OgreWrapper {
	class Node;
	class RenderScene;
	class Spline;
}
class LMVector3;

namespace LocoMotor {
	class GameObject;
	class EnemyAI : public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "EnemyAI";
		};
		EnemyAI();
		~EnemyAI();
		/// @brief Sets the initial position of the listener to the gameobject's
		void Start(OgreWrapper::Spline* splineToFollow);

		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
	private:
		//OgreWrapper::RenderScene* _renderScn;
		OgreWrapper::Node* _node; 
		LMVector3* currentNode;
		OgreWrapper::Spline* mySpline;
		LocoMotor::GameObject* myGbj;
		float timeStep,lastTimeStep;
	};
}