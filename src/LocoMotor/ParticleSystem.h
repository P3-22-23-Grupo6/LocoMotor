#ifndef LM_PARTICLESYS
#define LM_PARTICLESYS


#include "Component.h"
#include "Ogre.h"
#include "GameObject.h"
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

		void AddEmitter(std::string name, LMVector3 position);
		void AddEmitter(LMVector3 position);

		Ogre::ParticleEmitter* GetEmitter(std::string name);

		void RemoveEmitter(std::string name);
		void RemoveEmitter();
		
		void SetPosition(LMVector3 position);

		void SetDirection(LMVector3 direction);

		void SetRotation(LMVector3 rotation);
		void SetRotation(LMQuaternion rotation);

		void SetScale(LMVector3 scale);

		void SetVelocity(LMVector3 velocity);
		void SetVelocity(LMVector3 axis, float minVelocity, float maxVelocity);

		void SetVisible(bool visible);

		void SetEmitting(bool emitting);
		void SetSpeed(float speed);

		void SetAcceleration(LMVector3 axis, float acceleration);
		void SetAcceleration(LMVector3 axis, float minAcceleration, float maxAcceleration);

		void SetRotationSpeed(LMVector3 axis, float rotationSpeed);
		void SetRotationSpeed(LMVector3 axis, float minRotationSpeed, float maxRotationSpeed);

		void SetDuration(float duration);
		void SetDuration(float minDuration, float maxDuration);

		void SetRepeatDelay(float repeatDelay);
		void SetRepeatDelay(float minRepeatDelay, float maxRepeatDelay);

		void SetAngle(float angle);
		void SetAngle(float minAngle, float maxAngle);

		void SetColour(LMVector3 colour);
		void SetColour(LMVector3 minColour, LMVector3 maxColour);

		void SetTimeToLive(float timeToLive);
		void SetTimeToLive(float minTimeToLive, float maxTimeToLive);

		void SetTextureAnimation(int textureAnimation);
		void SetTextureAnimation(int minTextureAnimation, int maxTextureAnimation);
	private:
		Component* _comp;
		Ogre::ParticleSystem* _particleSystem;
		Ogre::SceneNode* _node;
		Ogre::SceneManager* _sceneManager;
		Ogre::Entity* _entity;
		Ogre::Vector3 _position;
		Ogre::Vector3 _scale;
		Ogre::Vector3 _rotation;
		std::map <std::string, Ogre::ParticleEmitter*> _emitters;
	};
}

#endif