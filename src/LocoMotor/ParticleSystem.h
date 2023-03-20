#include "Component.h"
#include "Ogre.h"
#include <string>

namespace LocoMotor {
	class ParticleSystem : public Component {
	public:
		ParticleSystem();
		~ParticleSystem();
		void Init(std::string name);
		void Update(float dt);
		void Render();
		void SetContext(GameObject* ent);
	private:
		Component* _comp;
		Ogre::ParticleSystem* _particleSystem;
		Ogre::SceneNode* _node;
		Ogre::SceneManager* _sceneManager;
		Ogre::Entity* _entity;
		Ogre::Vector3 _position;
		Ogre::Vector3 _scale;
		Ogre::Vector3 _rotation;
	};
}