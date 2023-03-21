#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"

namespace OgreWrapper {
	class RenderScene;
}

namespace LocoMotor {
	class Scene;
	class Camera : public Component {
	public:
		const static std::string name;

		Camera(Scene* scene, OgreWrapper::RenderScene* _renderScn);



		//GetCamera();
	};
}