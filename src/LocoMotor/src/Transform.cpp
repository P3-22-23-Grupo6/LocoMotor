#include "Transform.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "Node.h"

LocoMotor::Transform::Transform() {
	_position = LMVector3();
	_direction = LMQuaternion();
	_scale = LMVector3(1, 1, 1);

	_gObjNode = nullptr;
}

LocoMotor::Transform::~Transform() {
}

void LocoMotor::Transform::InitComponent() {
	gameObject->RegisterTransform(this);
	_gObjNode = gameObject->GetNode();
}

void LocoMotor::Transform::Init(std::vector<std::pair<std::string, std::string>>& params) {
	//TODO: como coooo
	for (const auto& pair : params) {
		if (pair.first == "pos" || pair.first == "position") {
			SetLocalPosition(LMVector3());
		}
		else if (pair.first == "rot" || pair.first == "rotation") {
			SetLocalRotation(LMQuaternion());
		}
		else if (pair.first == "size" || pair.first == "scale") {
			SetLocalScale(LMVector3());
		}
	}
}

void LocoMotor::Transform::Start() {
}

void LocoMotor::Transform::Update(const float dt) {
}

const LMVector3& LocoMotor::Transform::GetPosition() {
	return _position;
}

void LocoMotor::Transform::SetPosition(const LMVector3& newPosition) {
	SetLocalPosition(newPosition);
	SetPhysPosition(newPosition);
}

const LMQuaternion& LocoMotor::Transform::GetRotation() {
	return _direction;
}

void LocoMotor::Transform::SetRotation(const LMQuaternion& newRotation) {
	SetLocalRotation(newRotation);
	SetPhysRotation(newRotation);
}

const LMVector3& LocoMotor::Transform::GetSize() {
	return _scale;
}

void LocoMotor::Transform::SetSize(const LMVector3& newSize) {
	SetLocalScale(newSize);
	SetPhysScale(newSize);
	/*
	auto rb = gameObject->GetComponent<RigidBodyComponent>();
	if (rb != nullptr) {
		rb->sca(_direction);
	}
	*/
}

void LocoMotor::Transform::SetUpwards(const LMVector3& newUpward) {
	double angle = GetRotation().Up().Angle(newUpward);
	if (angle == 0.) return;


	//LMVector3 axis = GetRotation().Up() * newUpward;
	// Producto vectorial para hallar el vector perpendicular a otros dos vectores
	// Despues pasar esto al LMVectoresque :TODO

	LMVector3 v1 = GetRotation().Up();
	LMVector3 v2 = newUpward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}

void LocoMotor::Transform::SetLocalPosition(const LMVector3& newPosition) {
	_position = newPosition;
	_gObjNode->SetPosition(newPosition.GetX(), newPosition.GetY(), newPosition.GetZ());
}

void LocoMotor::Transform::SetLocalRotation(const LMQuaternion& newRotation) {
	_direction = newRotation;
	_direction.Normalize();
	Ogre::Quaternion a = newRotation.LmToOgre(newRotation);
	_gObjNode->SetOrientation(a);
}

void LocoMotor::Transform::SetLocalScale(const LMVector3& newSize) {
	_scale = newSize;
	_gObjNode->SetScale(newSize.GetX(), newSize.GetY(), newSize.GetZ());
}

void LocoMotor::Transform::SetPhysPosition(const LMVector3& newPosition) {
	auto rb = gameObject->GetComponent<RigidBodyComponent>();
	if (rb != nullptr) {
		rb->setPosition(newPosition);
	}
}

void LocoMotor::Transform::SetPhysRotation(const LMQuaternion& newRotation) {
	auto rb = gameObject->GetComponent<RigidBodyComponent>();
	if (rb != nullptr) {
		rb->setRotation(_direction);
	}
}

void LocoMotor::Transform::SetPhysScale(const LMVector3& newsize) {
}

void LocoMotor::Transform::LookAt(const LMVector3& lookPos) {
	_gObjNode->LookAt(lookPos.GetX(), lookPos.GetY(), lookPos.GetZ());
}
