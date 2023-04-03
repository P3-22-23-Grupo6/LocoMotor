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

	class Checkpoint : public Component {
	public:
		const static std::string name;

		// Para crear la camara se necesita tanto la escena como la escena de Render
		// 
		Checkpoint();


		void InitComponent() override;
		void Update(float dt) override;
	};
}