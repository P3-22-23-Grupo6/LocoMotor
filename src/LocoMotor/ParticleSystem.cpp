#include "ParticleSystem.h"

using namespace LocoMotor;
ParticleSystem::ParticleSystem() {
	_comp = nullptr;
	_particleSystem = nullptr;
	_node = nullptr;
	_sceneManager = nullptr;
	_entity = nullptr;
	_position = Ogre::Vector3::ZERO;
	_scale = Ogre::Vector3::ZERO;
	_rotation = Ogre::Vector3::ZERO;
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::Init(std::string name) {
	_sceneManager = _comp->GetContext()->GetSceneManager();
	_entity = _comp->GetContext()->GetComponent<Ogre::Entity>();
	_node = _comp->GetContext()->GetNode();
	_position = LMVector3::LmToOgre(_comp->GetContext()->GetTransform().position);
	_scale = LMVector3::LmToOgre(_comp->GetContext()->GetTransform().scale);
	_rotation = LMVector3::LmToOgre(_comp->GetContext()->GetTransform().rotation);
	_particleSystem = _sceneManager->createParticleSystem(_entity->getName() + "ParticleSystem", ("Examples/" + name));
	_node->attachObject(_particleSystem);
}

void ParticleSystem::Update(float dt) {
}

void ParticleSystem::Render() {


}

void ParticleSystem::SetContext(GameObject* ent) {
	_comp = ent->GetComponent<LocoMotor::ParticleSystem>();
}

void ParticleSystem::SetPosition(LMVector3 position) {
	_position = LMVector3::LmToOgre(position);
	_node->setPosition(_position);
}

void ParticleSystem::SetDirection(LMVector3 direction) {
	_node->setDirection(LMVector3::LmToOgre(direction));
}

void ParticleSystem::SetRotation(LMVector3 rotation) {
	_rotation = LMVector3::LmToOgre(rotation);
	_node->setOrientation(Ogre::Quaternion(Ogre::Degree(_rotation.x), Ogre::Vector3::UNIT_X) * Ogre::Quaternion(Ogre::Degree(_rotation.y), Ogre::Vector3::UNIT_Y) * Ogre::Quaternion(Ogre::Degree(_rotation.z), Ogre::Vector3::UNIT_Z));
}

void ParticleSystem::SetRotation(LMQuaternion rotation) {
	_node->setOrientation(LMQuaternion::LmToOgre(rotation));
}

void ParticleSystem::SetScale(LMVector3 scale) {
	_scale = LMVector3::LmToOgre(scale);
	_node->setScale(_scale);
}

void ParticleSystem::SetVelocity(LMVector3 velocity) {
	_particleSystem->setVelocity(LMVector3::LmToOgre(velocity));
}

void ParticleSystem::SetVelocity(LMVector3 axis, float minVelocity, float maxVelocity) {
	_particleSystem->setVelocity(LMVector3::LmToOgre(axis), minVelocity, maxVelocity);
}

void ParticleSystem::SetVisible(bool visible) {
	_particleSystem->setVisible(visible);
}

void ParticleSystem::SetEmitting(bool emitting) {
	_particleSystem->setEmitting(emitting);
}

void ParticleSystem::SetSpeed(float speed) {
	_particleSystem->setSpeed(speed);
}

void ParticleSystem::SetAcceleration(LMVector3 axis, float acceleration) {
	_particleSystem->setAcceleration(LMVector3::LmToOgre(axis), acceleration);
	_particleSystem->
}

void ParticleSystem::SetAcceleration(LMVector3 axis, float minAcceleration, float maxAcceleration) {
	_particleSystem->setAcceleration(LMVector3::LmToOgre(axis), minAcceleration, maxAcceleration);
}

void ParticleSystem::SetDuration(float duration) {
	_particleSystem->setDuration(duration);
}

void ParticleSystem::SetRepeatDelay(float repeatDelay) {
	_particleSystem->setRepeatDelay(repeatDelay);
}

void ParticleSystem::SetRepeatDelay(float minRepeatDelay, float maxRepeatDelay) {
	_particleSystem->setRepeatDelay(minRepeatDelay, maxRepeatDelay);
}



