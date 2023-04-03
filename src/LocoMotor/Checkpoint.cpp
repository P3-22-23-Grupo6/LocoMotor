#include "Checkpoint.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

#include "RigidBodyComponent.h"

using namespace LocoMotor;

const std::string Checkpoint::name = "Checkpoint";

LocoMotor::Checkpoint::Checkpoint(GameObject* player) {

	_player = player;
	//_rigidbody = gameObject->GetComponent<RigidBodyComponent>();
}

void LocoMotor::Checkpoint::Start() {
	
	// Acceder al componente Rigidbody
	_rb = gameObject->GetComponent<RigidBodyComponent>();
	if (_rb == nullptr)
		std::cout << "[ERROR] : Rigidbody needed for Checkpoint";
}

void LocoMotor::Checkpoint::Update(float dt) {

	if (_rb->checkCollision(_player))
		std::cout << "COLLISION" << "\n" << "\n" << "\n";
}
