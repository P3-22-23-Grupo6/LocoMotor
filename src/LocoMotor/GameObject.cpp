#include "GameObject.h"
#include "Transform.h"

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

	_node = node;

	tiltAmount = 0.0f;//TEMPORAL
}

// Update the GameObject
void GameObject::Update(float dt) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
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

	// MOVIMIENTO CALCULADO CON MATES :TODO
	if (!physicsBasedMovement)
		rbComp->useGravity(LMVector3(0, 0, 0));


		//RAYCAST TEMPORAL
	LMVector3 from = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y(), _node->GetPosition_Z());
	LMVector3 to = LMVector3(_node->GetPosition_X(), _node->GetPosition_Y() - 20, _node->GetPosition_Z());

	LMVector3 upVector = GetTransform()->GetRotation().Up();
	upVector.Normalize();

	//double verticalAxisMargin = 2;
	//from = from + LMVector3(upVector.GetX() * verticalAxisMargin, upVector.GetY() * verticalAxisMargin, upVector.GetZ() * verticalAxisMargin);

	double raycastDistance = 7;
	upVector = LMVector3(upVector.GetX() * raycastDistance, upVector.GetY() * raycastDistance, upVector.GetZ() * raycastDistance);
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		// std::cout << "Collision! *****************";
		//_node->Rotate(0, 3, 0);
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);

		//n.Normalize();
		std::cout << "\n" << "NORMAL = " << n.GetX() << ", " << n.GetY() << ", " << n.GetZ() << "\n";

		//LMVector3 p = rbComp->GetraycastHitPoint(from, to) + n;
		//std::cout << "\n" << "CarPos = " << p.GetX() << ", " << p.GetY() << ", " << p.GetZ() << "\n";


		//GetTransform()->GetRotation().GetX()
		//LMVector3 p = rbComp->GetraycastHitPoint(from, to) + n;
		//std::cout << "\n" << "CarPos = " << p.GetX() << ", " << p.GetY() << ", " << p.GetZ() << "\n";

		//LMVector3 prueba = LMVector3(0, 5, 6);
		//prueba.Normalize();


		// MOVIMIENTO CALCULADO CON MATES :TODO

		if (!physicsBasedMovement) {
			//Intensidad con la que se va a actualizar el vector normal del coche
			float pitchIntensity = 40;
			LMVector3 newUp = LMVector3(n.GetX() * pitchIntensity, n.GetY() * pitchIntensity, n.GetZ() * pitchIntensity);
			GetTransform()->SetUpwards(newUp);

			LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
			double hoverDist = 4;
			LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
			GetTransform()->SetPosition(hitPos + hoverDisplacement);
		}
	}
	else {
		//std::cout << "NO COLL! *****************";
	}
	bool acelerate = man->GetKey(SDL_SCANCODE_W);
	if (acelerate) {

		double degToRad = 0.0174533;

		// MOVIMIENTO CON FISICAS :TODO
		// Para que funcione, la gravedad tiene que estar activada y el objeto tener una masa distinta de 0
		if (physicsBasedMovement)
			GetComponent<RigidBodyComponent>()->addForce(transform->GetRotation().Forward() * 10 * dt);

			// MOVIMIENTO CALCULADO CON MATES :TODO
		else {
			LMVector3 forward = GetTransform()->GetRotation().Forward();
			forward.Normalize();
			double speed = 14;
			forward = LMVector3(forward.GetX() * speed, forward.GetY() * speed, forward.GetZ() * speed);
			GetTransform()->SetPosition(GetTransform()->GetPosition() + forward);
		}




		//_rigidBody->AddForce(LMVector3(0, 0, 1));
		//SetPosition(LMVector3(100, 10, 10));
		//_node->Translate(0, 0, 1);
	}

	bool rotateRight = man->GetKey(SDL_SCANCODE_A);
	if (rotateRight) {
		transform->SetRotation(transform->GetRotation().Rotate(transform->GetRotation().Up(), 2.));
	}
	bool rotateLeft = man->GetKey(SDL_SCANCODE_D);
	if (rotateLeft) {
		/*
		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, -1, 0, 0));
		//_rigidBody->setRotation(LMQuaternion(1, -1, 0, 0));
		_node->Rotate(0, -3, 0);
		*/
		transform->SetRotation(transform->GetRotation().Rotate(transform->GetRotation().Up(), -2.));
	}

	std::cout << transform->GetRotation().GetY() << std::endl;
}


void LocoMotor::GameObject::AddComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params) {
	if (_componentsByName.count(name) > 0) {
		return;
	}
	Component* comp = ComponentsFactory::GetInstance()->CreateComponent(name);
	comp->SetContext(this);
	comp->Init(params);
	_componentsByName.insert({ name, comp });
	if (name == "Transform") {
		transform = dynamic_cast<Transform*>(comp);
	}
}


// Set the position of the GameObject
void GameObject::SetPosition(LMVector3 pos) {
	transform->SetPosition(pos);
}

void LocoMotor::GameObject::SetRotation(LMQuaternion rot) {
	transform->SetRotation(rot);
}

// Set the scale of the GameObject
void GameObject::SetScale(LMVector3 sc) {
	transform->SetSize(sc);
}

// Get the transform of the GameObject
Transform* GameObject::GetTransform() {
	return transform;
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



void GameObject::StartComp() {
	for (auto comp : _componentsByName) {
		comp.second->Start();
	}
}

void LocoMotor::GameObject::RegisterTransform(Transform* newTrans) {
	transform = newTrans;
}


// Destructor
GameObject::~GameObject() {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}