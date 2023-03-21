#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"

namespace OgreWrapper {
	class RenderScene;
	class Node;
}

namespace LocoMotor {
	class Scene;
	class GameObject;

	class Camera : public Component {
	public:
		const static std::string name;

		Camera(Scene* _scene, OgreWrapper::RenderScene* _renderScn);

		OgreWrapper::Node* _node;

		void InitComponent() override;
		void Update(float dt) override;

	private:
		Scene* _scene;
		OgreWrapper::RenderScene* _renderScn;

		//GetCamera();
	};
}