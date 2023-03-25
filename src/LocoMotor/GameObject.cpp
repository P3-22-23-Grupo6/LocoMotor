#include "GameObject.h"

//HITO 1 POC
#include "InputManager.h"
#include "Renderer3D.h"
#include "BulletRigidBody.h"
#include "Node.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject() {
	_tr.direction = LMQuaternion();
	_tr.position = LMVector3();
	_tr.rotation = LMVector3();
	_tr.scale = LMVector3();
}

// Update the GameObject
void GameObject::Update(float dt) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		it->second->Update(dt);
	}
	if (_rigidBody == nullptr) return;
	InputManager* man = InputManager::Get();

	if (man->controllerConnected()) {

		float gyroRotate = man->GetGyroscopeAngularSpeed(InputManager::Axis::Horizontal);
		float joystickValue_1_Hor = man->GetJoystickValue(1, InputManager::Axis::Horizontal);
		//_node->Rotate(0, joystickValue_1_Hor * 5, -gyroRotate * 200);
		_node->Rotate(0, gyroRotate * 200 + -joystickValue_1_Hor * 5, 0);

		float joystickValue_0_Hor = man->GetJoystickValue(0, InputManager::Axis::Horizontal);
		float joystickValue_0_Ver = man->GetJoystickValue(0, InputManager::Axis::Vertical);

		float verticalMov = 0;
		if (man->GetButton(SDL_CONTROLLER_BUTTON_A)) {
			verticalMov = .1f;
		}
		else if (man->GetButton(SDL_CONTROLLER_BUTTON_B))
			verticalMov = -.1f;

		_rigidBody->AddForce(LMVector3(joystickValue_0_Hor, verticalMov, joystickValue_0_Ver));
		_node->Translate(-joystickValue_0_Hor, verticalMov, -joystickValue_0_Ver);

	}

	bool rotateRight = man->GetKey(SDL_SCANCODE_A);
	if (rotateRight) {
		_rigidBody->setRotation(LMQuaternion(1, -1, 0, 0));
		_node->Rotate(0, -1, 0);
	}
	bool rotateLeft = man->GetKey(SDL_SCANCODE_D);
	if (rotateLeft) {
		_rigidBody->setRotation(LMQuaternion(1, 1, 0, 0));
		_node->Rotate(0, 1, 0);
	}
}

// Set the position of the GameObject
void GameObject::SetPosition(LMVector3 pos) {
	_tr.position = pos;
}
// Set the rotation of the GameObject
void GameObject::SetRotation(LMVector3 rot) {
	_tr.rotation = rot;
}

// Set the transform direction of the GameObject
void GameObject::SetDirection(LMQuaternion dir) {
	_tr.direction = dir;
}

// Set the scale of the GameObject
void GameObject::SetScale(LMVector3 sc) {
	_tr.scale = sc;
}
// Get the transform of the GameObject
Transform GameObject::GetTransform() {
	return _tr;
}

//HITO 1 POC
// Set the rigid body of the GameObject
void LocoMotor::GameObject::SetRigidBody(PhysicsWrapper::BulletRigidBody* rb) {
	_rigidBody = rb;
}
// Set the renderer of the GameObject
void LocoMotor::GameObject::SetRenderer(OgreWrapper::Renderer3D* renderer, OgreWrapper::Node* node) {
	_renderer = renderer;
	_node = node;
	_node->Attach(_renderer);
}

void LocoMotor::GameObject::SetContext(Scene* scn)
{
	scene = scn;
}

Scene* LocoMotor::GameObject::GetScene()
{
	return scene;
}



// Destructor
GameObject::~GameObject() {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}