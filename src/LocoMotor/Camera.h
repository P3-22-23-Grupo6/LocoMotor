#pragma once

//namespace LocoMotor {
//	class Component;
//}
#include "Component.h"

namespace LocoMotor {
	class Camera : public Component {
	public:
		const static std::string name;

		Camera();
	};
}