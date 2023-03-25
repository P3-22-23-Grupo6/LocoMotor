#include "ParticleSystem.h"
#include "LocoMotor_Ogre/include/ParticleHelper.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

using namespace LocoMotor;

const std::string ParticleSystem::name = "ParticleSystem";

ParticleSystem::ParticleSystem(Scene* scene, OgreWrapper::RenderScene* renderScn, std::string filename) {
	_scene = scene;
	_renderScn = renderScn;
	_filename = filename;
}

void ParticleSystem::InitComponent() {
	//Crear nodo
	_node = _renderScn->CreateNode("ParticleNode");
	//Crear particulas
	_particleHelper = _renderScn->CreateParticleHelper("ParticleHelper", _filename);
	//Attachear al nodo del gameObject
	OgreWrapper::RenderEntity* renderObj = (OgreWrapper::RenderEntity*) this;
	gameObject->GetNode()->Attach(renderObj);
	//SetNode al gameObject
}

void ParticleSystem::Update(float dt) {
	if (_node != nullptr) {
		float x = gameObject->GetNode()->GetPosition_X();
		float y = gameObject->GetNode()->GetPosition_Y();
		float z = gameObject->GetNode()->GetPosition_Z();
		_node->SetPosition(x, y, z);
	}
}
