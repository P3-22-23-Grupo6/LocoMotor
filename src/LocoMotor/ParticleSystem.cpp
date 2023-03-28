#include "ParticleSystem.h"
#include "LocoMotor_Ogre/include/ParticleHelper.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

using namespace LocoMotor;

std::string ParticleSystem::name = "ParticleSystem";

ParticleSystem::ParticleSystem(std::string sysName, OgreWrapper::RenderScene* renderScn, std::string filename) {
	_name = sysName;
	_renderScn = renderScn;
	_filename = filename;
}

void ParticleSystem::InitComponent() {
	//Crear nodo
	_node = _renderScn->CreateNode("ParticleNode");
	//Crear particulas
	_particleHelper = _renderScn->CreateParticleHelper(_name + "ParticleHelper", _filename);
	//Attachear al nodo del gameObject
	gameObject->GetNode()->Attach(_particleHelper);
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



