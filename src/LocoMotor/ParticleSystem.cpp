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

void ParticleSystem::Init() {
	_sceneManager = _comp->GetContext()->GetSceneManager();
	_entity = _comp->GetContext()->GetEntity();
	_node = _comp->GetContext()->GetNode();
	_position = _comp->GetContext()->GetPosition();
	_scale = _comp->GetContext()->GetScale();
	_rotation = _comp->GetContext()->GetRotation();
	_particleSystem = _sceneManager->createParticleSystem(_entity->getName() + "ParticleSystem", "Examples/Smoke");
	_node->attachObject(_particleSystem);
}

void ParticleSystem::Update(float dt) {
}

void ParticleSystem::Render() {
}

void ParticleSystem::SetContext(GameObject* ent) {
	_comp = ent->GetComponent("ParticleSystem");
}