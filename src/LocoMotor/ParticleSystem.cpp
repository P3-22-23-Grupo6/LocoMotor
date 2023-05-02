#include "ParticleSystem.h"
#include "LocoMotor_Ogre/include/ParticleHelper.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Node.h"
#include "OgreManager.h"
#include "LogSystem.h"

using namespace LocoMotor;

/**
 * This is the constructor for a particle system object in C++.
 */
LocoMotor::ParticleSystem::ParticleSystem()
{
	_renderScn = nullptr;
	_particleHelper = nullptr;

	_filename = "Racers/JetEngine2";
	_name = "smoke";
}


/**
 * The function initializes the particle system by setting its name and filename based on the input
 * parameters.
 * @brief Initializes the particle system by setting its name and filename based on the input
 * @param params A vector of pairs, where each pair contains a string key and a string value. These
 * pairs represent the parameters passed to the Init() function.
 */
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

/**
 * This function initializes a particle system component by creating a node, creating particles,
 * attaching them to the node of the game object, and setting the node to the game object.
 * @brief Initializes a particle system component by creating a node, creating particles,
 */
void ParticleSystem::InitComponent() {
	_renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	//Crear nodo
	_node = _renderScn->CreateNode("ParticleNode");
	//Crear particulas
	_particleHelper = _renderScn->CreateParticleHelper(_name + "ParticleHelper", _filename);
	//Attachear al nodo del gameObject
	if (_particleHelper != nullptr)
		_renderScn->GetNode(gameObject->GetName())->Attach(_particleHelper);
	else {
		LocoMotor::LogSystem::GetInstance()->Save(0, "Couldn't initialize ParticleSystem named '" + _name + "' on file '" + _filename + "'");
	}
	//SetNode al gameObject
}

/**
 * The function updates the position of a particle system node based on the position of its associated
 * game object.
 * 
 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
 * used to ensure that the particle system updates at a consistent rate regardless of the frame rate.
 */
void ParticleSystem::Update(float dt) {
	if (_node != nullptr) {
		float x = gameObject->GetTransform()->GetPosition().GetX();
		float y = gameObject->GetTransform()->GetPosition().GetY();
		float z = gameObject->GetTransform()->GetPosition().GetZ();
		_node->SetPosition(x, y, z);
	}
}



