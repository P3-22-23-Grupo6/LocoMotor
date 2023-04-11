#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"
#include "LMVector.h"

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
		static std::string GetName() {
			return "Camera";
		};
		// Para crear la camara se necesita tanto la escena como la escena de Render
		// 
		Camera();
		
		OgreWrapper::Node* _node;

		void InitComponent() override;
		void Update(float dt) override;

		void SetTarget(GameObject* target, LMVector3 offset);

	private:
		Scene* _scene;
		OgreWrapper::RenderScene* _renderScn;

		GameObject* _target;
		LMVector3 _offset;

		//GetCamera();
	};
}