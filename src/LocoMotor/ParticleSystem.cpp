#include "ParticleSystem.h"
#include "LocoMotor_Ogre/include/ParticleHelper.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Node.h"
#include "OgreManager.h"

using namespace LocoMotor;

LocoMotor::ParticleSystem::ParticleSystem()
{
	_renderScn = nullptr;
	_particleHelper = nullptr;

	_filename = "Racers/JetEngine2";
	_name = "smoke";
}


void LocoMotor::ParticleSystem::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "name") {
			_name = params[i].second;
		}
		else if (params[i].first == "file") {
			_filename = params[i].second;
		}
	}
}

void ParticleSystem::InitComponent() {
	_renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	//Crear nodo
	_node = _renderScn->CreateNode("ParticleNode");
	//Crear particulas
	_particleHelper = _renderScn->CreateParticleHelper(_name + "ParticleHelper", _filename);
	//Attachear al nodo del gameObject
	_renderScn->GetNode(gameObject->GetName())->Attach(_particleHelper);
	//SetNode al gameObject
}

void ParticleSystem::Update(float dt) {
	if (_node != nullptr) {
		float x = gameObject->GetTransform()->GetPosition().GetX();
		float y = gameObject->GetTransform()->GetPosition().GetY();
		float z = gameObject->GetTransform()->GetPosition().GetZ();
		_node->SetPosition(x, y, z);
	}
}



