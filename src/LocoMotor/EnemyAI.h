#pragma once
#include <string>
#include "Component.h"
#include <OgreSimpleSpline.h>

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
		void Start(LocoMotor::GameObject* enemyGbj, OgreWrapper::Node* node, Ogre::SimpleSpline* ogreSpline);

		/// @brief Updates the listener's world attributes to be the same as the gameobject's
		/// @param dt DeltaTime used to calculate the velocity
		void Update(float dt) override;
	private:
		OgreWrapper::RenderScene* _renderScn;
		OgreWrapper::Node* _node; 
		OgreWrapper::Node* currentNode;
		Ogre::SimpleSpline* mySpline;
		LocoMotor::GameObject* myGbj;
	};
}