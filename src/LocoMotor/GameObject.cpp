#include "GameObject.h"

//HITO 1 POC
#include "InputManager.h"
#include "Scene.h"
#include "Node.h"
//Borrar luego
#include "SceneManager.h"
#include "RigidBodyComponent.h"
#include "OpenSteer/SimpleVehicle.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject(OgreWrapper::Node* node) {
	_tr.direction = LMQuaternion();
	_tr.position = LMVector3();
	_tr.rotation = LMVector3();
	_tr.scale = LMVector3(1,1,1);

	_node = node;

	tiltAmount = 0.0f;//TEMPORAL
}

// Update the GameObject
void GameObject::Update(float dt) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if(it->second->isEnabled())
		it->second->Update(dt);
	}
	if (GetComponent<RigidBodyComponent>() == nullptr) return;
	InputManager* man = InputManager::Get();
	if (!movable)return;
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

		RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
		rbComp->addForce(LMVector3(joystickValue_0_Hor, verticalMov, joystickValue_0_Ver));
		_node->Translate(-joystickValue_0_Hor, verticalMov, -joystickValue_0_Ver);

		

		SetPosition(LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z()));
	}
	RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
	//RAYCAST TEMPORAL
	LMVector3 from = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z());
	LMVector3 to = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y() - 5, _node->GetPosition_Z());
	if (rbComp->GetRaycastHit(from, to)) {
		std::cout << "Collision! *****************";
		//_node->Rotate(0, 3, 0);
	}
	else std::cout << "NO COLL! *****************";

	bool acelerate = man->GetKey(SDL_SCANCODE_W);
	if (acelerate) {

		double degToRad = 0.0174533;

		GetComponent<RigidBodyComponent>()->addForce(LMVector3(-20 * std::sin(_tr.rotation.GetY() * degToRad), 0, -20 * std::cos(_tr.rotation.GetY() * degToRad)) * dt);
		//_rigidBody->AddForce(LMVector3(0, 0, 1));
		//SetPosition(LMVector3(100, 10, 10));
		//_node->Translate(0, 0, 1);
	}

	bool rotateRight = man->GetKey(SDL_SCANCODE_A);
	if (rotateRight) {
		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, 1, 0, 0));
		//_rigidBody->setRotation(LMQuaternion(1, 1, 0, 0));
		_node->Rotate(0, 3, 0);
		_tr.rotation.SetY(_tr.rotation.GetY() + 3.);
	}
	bool rotateLeft = man->GetKey(SDL_SCANCODE_D);
	if (rotateLeft) {
		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, -1, 0, 0));
		//_rigidBody->setRotation(LMQuaternion(1, -1, 0, 0));
		_node->Rotate(0, -3, 0);
		_tr.rotation.SetY(_tr.rotation.GetY() - 3.);
	}

	std::cout << _tr.rotation.GetY() << std::endl;
}


void LocoMotor::GameObject::AddComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params) {
	if (_componentsByName.count(name) > 0) {
		return;
	}
	Component* comp = ComponentsFactory::GetInstance()->CreateComponent(name);
	comp->SetContext(this);
	comp->Init(params);
	_componentsByName.insert({ name, comp });
}


// Set the position of the GameObject
void GameObject::SetPosition(LMVector3 pos) {
	_tr.position = pos;
	_node->SetPosition(_tr.position.GetX(), _tr.position.GetY(), _tr.position.GetZ()); // Todo: Revisar
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

// Set the renderer of the GameObject
void LocoMotor::GameObject::SetRenderer(OgreWrapper::Node* node) {
	_node = node;
}

void LocoMotor::GameObject::SetContext(Scene* scn) {
	scene = scn;
}

Scene* LocoMotor::GameObject::GetScene() {
	return scene;
}

OgreWrapper::Node* LocoMotor::GameObject::GetNode() {
	return _node;
}



void GameObject::StartComp(){
	for (auto comp : _componentsByName) {
		comp.second->Start();
	}
}


// Destructor
GameObject::~GameObject() {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}