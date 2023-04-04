#include "Checkpoint.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

#include "RigidBodyComponent.h"

using namespace LocoMotor;

const std::string Checkpoint::name = "Checkpoint";

LocoMotor::Checkpoint::Checkpoint(GameObject* player, int checkpointIndex) {

	_player = player;
	_checkpointIndex = checkpointIndex;
}

void LocoMotor::Checkpoint::Start() {
	
	// Acceder al componente Rigidbody
	_rb = gameObject->GetComponent<RigidBodyComponent>();
	if (_rb == nullptr)
		std::cout << "[ERROR] : Rigidbody needed for Checkpoint";
}

void LocoMotor::Checkpoint::Update(float dt) {

	// COLISION

	//if (_rb->checkCollision(_player))
	//	// Comunicar al racemanager que este checkpoint ha sido alcanzado por el jugador
	//	std::cout << "COLLISION" << "\n" << "\n";


	// DISTANCIAS
	float distance = (_player->GetTransform().position - gameObject->GetTransform().position).Magnitude();

	if (distance < 40)
		checked = true;


	std::cout << "DISTANCE = " << distance << "\n";
}
