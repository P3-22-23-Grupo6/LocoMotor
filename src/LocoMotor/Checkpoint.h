#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"
#include "lmVector.h"

//namespace OgreWrapper {
//	class RenderScene;
//	class Node;
//}

namespace LocoMotor {
	class Scene;
	class GameObject;
	class RigidBodyComponent;

	class Checkpoint : public Component {
	public:
		const static std::string name;

		Checkpoint(GameObject* player = nullptr, int checkpointIndex = 0);

		void Start() override;
		void Update(float dt) override;

	private:

		int _checkpointIndex;
		bool checked; // Si el jugador ya ha alcanzado este checkpoint en esta vuelta

		RigidBodyComponent* _rb;
		GameObject* _player;
	};
}