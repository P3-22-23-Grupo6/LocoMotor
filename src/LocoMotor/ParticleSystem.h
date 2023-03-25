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
		const static std::string name;
		ParticleSystem(Scene* scene, OgreWrapper::RenderScene* renderScn, std::string filename);
		OgreWrapper::Node* _node;

		void InitComponent() override;

		void Update(float dt) override;
	private:
		Scene* _scene;
		OgreWrapper::RenderScene* _renderScn;
		OgreWrapper::ParticleHelper* _particleHelper;

		std::string _filename;
	};
}

#endif