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
#include "LmVectorConverter.h"

using namespace LocoMotor;

// Constructor
GameObject::GameObject(OgreWrapper::Node* node) {
	scene = nullptr;
	transform = nullptr;
	_renderer = nullptr;
	_node = node;
	_componentsByName = {};

	physicsBasedMovement = true;
	this->AddComponent("Transform");
	tiltAmount = 0.0f; //TEMPORAL
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
	//if (!physicsBasedMovement)
		rbComp->useGravity(LMVector3(0, 0, 0));


	LMVector3 from = GetTransform()->GetPosition();
	LMVector3 to = from + LMVector3(0, -20, 0);

	LMVector3 upVector = GetTransform()->GetRotation().Up();
	upVector.Normalize();
	double raycastDistance = 20;
	upVector = upVector * raycastDistance;
	to = from - upVector;

	if (rbComp->GetRaycastHit(from, to)) {
		LMVector3 n = rbComp->GethasRaycastHitNormal(from, to);
		
		// MOVIMIENTO CALCULADO CON MATES :TODO
		// if (!physicsBasedMovement) {
			//Intensidad con la que se va a actualizar el vector normal del coche
			float pitchIntensity = 40;
			LMVector3 newUp = n * pitchIntensity;
			GetTransform()->SetUpwards(newUp);

			LMVector3 hitPos = rbComp->GetraycastHitPoint(from, to);
			double hoverDist = 7;
			LMVector3 hoverDisplacement = LMVector3(n.GetX() * hoverDist, n.GetY() * hoverDist, n.GetZ() * hoverDist);
			GetTransform()->SetPosition(hitPos + hoverDisplacement);
		// }
	}
	else {
		// Si no detecta suelo, que se caiga
		localVelocity = localVelocity + LMVector3(0, -.2f, 0);
	}


	bool acelerate = man->GetKey(SDL_SCANCODE_W);
	if (acelerate) {

		// MOVIMIENTO CON FISICAS :TODO
		// Para que funcione, la gravedad tiene que estar activada y el objeto tener una masa distinta de 0
		if (physicsBasedMovement)
			GetComponent<RigidBodyComponent>()->addForce(transform->GetRotation().Forward() * 40 * dt);

			// MOVIMIENTO CALCULADO CON MATES :TODO
		else {
			LMVector3 forward = GetTransform()->GetRotation().Forward();
			forward.Normalize();
			double speed = .5; //14;
			forward = LMVector3(forward.GetX() * speed, forward.GetY() * speed, forward.GetZ() * speed);
			//GetTransform()->SetPosition(GetTransform()->GetPosition() + forward);

			localVelocity = localVelocity + forward;
		}


		//_rigidBody->AddForce(LMVector3(0, 0, 1));
		//SetPosition(LMVector3(100, 10, 10));
		//_node->Translate(0, 0, 1);
	}

	// Desacelerar la velocidad actual para que no haya tanto derrape

	//LMVector3 localVel = BulletToLm(rbComp->getBody()->getLinearVelocity());
	LMVector3 localVel = rbComp->GetLinearVelocity();

	//btVector3 BULLETVECTOR = rbComp->getBody()->getLinearVelocity();

	LMVector3 forward = GetTransform()->GetRotation().Forward();
	double angle = localVel.Angle(forward);

	std::cout << "\n" << "ANGLE = " << angle;

	double intensity = localVel.Magnitude();

	localVel.Normalize();

	std::cout << "\n" << "LOCAL VEL = " << localVel.GetX()
		<< ", " << localVel.GetY() << ", " << localVel.GetZ() << "\n";

	LMVector3 invertedVelocity = localVel * -1;

	if (angle > .5f)
	if (physicsBasedMovement)
		GetComponent<RigidBodyComponent>()->addForce(invertedVelocity * intensity/20 * angle * dt);




	bool rotateRight = man->GetKey(SDL_SCANCODE_A);

	float torqueStrengh = 5.f;
	if (rotateRight) {
		if (physicsBasedMovement) {
			// TODO: quitar la referencia directa a btvector3 abajo tambien
			rbComp->getBody()->applyTorqueImpulse(btVector3(transform->GetRotation().Up().GetX(), transform->GetRotation().Up().GetY(), transform->GetRotation().Up().GetZ()) * torqueStrengh);
		}
		else
			transform->SetRotation(transform->GetRotation().Rotate(transform->GetRotation().Up(), 90. * dt / 1000.f));
	}
	bool rotateLeft = man->GetKey(SDL_SCANCODE_D);
	if (rotateLeft) {
		/*
		GetComponent<RigidBodyComponent>()->setRotation(LMQuaternion(1, -1, 0, 0));
		//_rigidBody->setRotation(LMQuaternion(1, -1, 0, 0));
		_node->Rotate(0, -3, 0);
		*/
		if (physicsBasedMovement) {
			rbComp->getBody()->applyTorqueImpulse(btVector3(transform->GetRotation().Up().GetX(), transform->GetRotation().Up().GetY(), transform->GetRotation().Up().GetZ()) * -torqueStrengh);
		}
		else
		transform->SetRotation(transform->GetRotation().Rotate(transform->GetRotation().Up(), -90. * dt / 1000.f));
	}

	// std::cout << transform->GetRotation().GetY() << std::endl;
	rbComp->getBody()->applyTorqueImpulse(btVector3(0, 0, rbComp->getBody()->getTotalTorque().getZ()));
	//rbComp->FreezeRotation(LMVector3(1, 1, 0));

	// Comprobacion para que no gire demasiado rapido
	if (rbComp->getBody()->getTotalTorque().length() > 100.f)
		rbComp->getBody()->applyTorqueImpulse(rbComp->getBody()->getTotalTorque() * -0.2f);

	// MOVIMIENTO CALCULADO CON MATES :TODO
	if (!physicsBasedMovement) {

	// Aplicar velocidad

	// Ralentizar velocidad
		float currentVelocity = (float)localVelocity.Magnitude();
		currentVelocity -= .2f;
		if (currentVelocity < 0) currentVelocity = 0;
		localVelocity.Normalize();
		localVelocity = LMVector3(localVelocity.GetX() * currentVelocity,
						  localVelocity.GetY() * currentVelocity,
						  localVelocity.GetZ() * currentVelocity);


	// Clamp localVelocity
		float maxVelocity = 10;

		if (localVelocity.Magnitude() > maxVelocity) {
			localVelocity.Normalize();
			localVelocity = LMVector3(localVelocity.GetX() * maxVelocity,
									  localVelocity.GetY() * maxVelocity,
									  localVelocity.GetZ() * maxVelocity);
		}


		// std::cout << "\n" << "localVelocity = " << localVelocity.GetX()
			// << ", " << localVelocity.GetY() << ", " << localVelocity.GetZ() << "\n";

		GetTransform()->SetPosition(GetTransform()->GetPosition() + localVelocity);


		if(GetTransform()->GetPosition().GetY() < -45)
		{
			GetTransform()->SetPosition(LMVector3(0,5,0));
		}
	}
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


void LocoMotor::GameObject::OnCollisionEnter(GameObject* other) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionEnter(other);
	}
}

void LocoMotor::GameObject::OnCollisionExit(GameObject* other) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionExit(other);
	}
}

void LocoMotor::GameObject::OnCollisionStay(GameObject* other) {
	std::map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionStay(other);
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
	for (auto& comp : _componentsByName) {
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