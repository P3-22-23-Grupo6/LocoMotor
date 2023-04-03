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

		Checkpoint(GameObject* player = nullptr);

		void Start() override;
		void Update(float dt) override;

	private:
		RigidBodyComponent* _rb;
		GameObject* _player;
	};
}