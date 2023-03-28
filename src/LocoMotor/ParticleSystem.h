#ifndef LM_PARTICLESYS
#define LM_PARTICLESYS

#include "Component.h"

namespace OgreWrapper {
	class ParticleHelper;
	class Node;
	class RenderScene;
}

namespace LocoMotor {
	class Scene;
	class GameObject;
	class ParticleSystem : public Component {
	public:
		static std::string name;
		ParticleSystem(std::string sysName, OgreWrapper::RenderScene* renderScn, std::string filename);
		OgreWrapper::Node* _node;

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