#ifndef LM_PARTICLESYS
#define LM_PARTICLESYS
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace OgreWrapper {
	class ParticleHelper;
	class Node;
	class RenderScene;
}

namespace LocoMotor {
	class Scene;
	class GameObject;
	class MOTOR_API ParticleSystem : public Component {
	public:
		static std::string name;
		static std::string GetName() {
			return "ParticleSystem";
		};
		ParticleSystem();
		OgreWrapper::Node* _node;
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitComponent() override;

		void Update(float dt) override;

		bool allowMultiple = true;

	private:
		OgreWrapper::RenderScene* _renderScn;
		OgreWrapper::ParticleHelper* _particleHelper;

		std::string _filename;
		std::string _name;
	};
}

#endif