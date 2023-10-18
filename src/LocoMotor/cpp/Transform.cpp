#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderScene.h"
#include "RigidBody.h"
#include "Node.h"
#include "OgreManager.h"
#include "LmVectorConverter.h"



LocoMotor::Transform::Transform() {
	_position = LMVector3();
	_localPosition = LMVector3();
	_direction = LMQuaternion();
	_scale = LMVector3(1, 1, 1);

	_gObjNode = nullptr;
	parent = nullptr;
}

LocoMotor::Transform::~Transform() {
}


void LocoMotor::Transform::InitComponent() {
	gameObject->RegisterTransform(this);
	_gObjNode = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName())->GetNode(gameObject->GetName());
}


void LocoMotor::Transform::Init(std::vector<std::pair<std::string, std::string>>& params) {
	gameObject->RegisterTransform(this);
	
	for (const auto& pair : params) {
		if (pair.first == "pos" || pair.first == "position") {
			unsigned char currAxis = 0;
			std::string num = "";
			LMVector3 result = LMVector3();
			for (const char c : pair.second) {
				if (c != ' ') {
					num += c;
				}
				else {
					float value = 0.f;
					try {
						value = std::stof(num);
					}
					catch (std::invalid_argument) {
						value = 0.f;
					}
					if (currAxis == 0) {
						result.SetX(value);
					}
					else if (currAxis == 1) {
						result.SetY(value);
					}
					else if (currAxis == 2) {
						result.SetZ(value);
					}
					currAxis++;
					num = "";
				}
			}
			float value = 0.0f;
			try {
				value = std::stof(num);
			}
			catch (std::invalid_argument) {
				value = 0.0f;
			}
			if (currAxis == 2) {
				result.SetZ(value);
			}
			_position = result;
		
		}
		else if (pair.first == "rot" || pair.first == "rotation") {
			unsigned char currAxis = 0;
			std::string num = "";
			LMVector3 result = LMVector3();
			for (const char c : pair.second) {
				if (c != ' ') {
					num += c;
				}
				else {
					float value = 0.f;
					try {
						value = std::stof(num);
					}
					catch (std::invalid_argument) {
						value = 0.f;
					}
					if (currAxis == 0) {
						result.SetX(value);
					}
					else if (currAxis == 1) {
						result.SetY(value);
					}
					else if (currAxis == 2) {
						result.SetZ(value);
					}
					currAxis++;
					num = "";
				}
			}
			float value = 0.0f;
			try {
				value = std::stof(num);
			}
			catch (std::invalid_argument) {
				value = 0.0f;
			}
			if (currAxis == 2) {
				result.SetZ(value);
			}
			_direction = result.AsRotToQuaternion();
			_direction.Normalize();
		}
		else if (pair.first == "size" || pair.first == "scale") {
			unsigned char currAxis = 0;
			std::string num = "";
			LMVector3 result = LMVector3();
			for (const char c : pair.second) {
				if (c != ' ') {
					num += c;
				}
				else {
					float value = 0.f;
					try {
						value = std::stof(num);
					}
					catch (const char*) {
						value = 0.f;
					}
					if (currAxis == 0) {
						result.SetX(value);
					}
					else if (currAxis == 1) {
						result.SetY(value);
					}
					else if (currAxis == 2) {
						result.SetZ(value);
					}
					currAxis++;
					num = "";
				}
			}
			float value = 0.0f;
			try {
				value = std::stof(num);
			}
			catch (const char*) {
				value = 0.0f;
			}
			if (currAxis == 2) {
				result.SetZ(value);
			}
			_scale = result;
		}
	}
}

void LocoMotor::Transform::InitRuntime(LMVector3 initPos, LMVector3 initRot, LMVector3 initScale) {
	gameObject->RegisterTransform(this);

	_position = initPos;
	_localPosition = LMVector3();
	_direction = initRot.AsRotToQuaternion();
	_localDirection = LMQuaternion();
	_scale = initScale;
	_localScale = LMVector3(1,1,1);
}

void LocoMotor::Transform::Start() {
	_gObjNode = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName())->GetNode(gameObject->GetName());
	SetPosition(_position);
	SetRotation(_direction);
	SetSize(_scale);
}

void LocoMotor::Transform::Update(const float dt) {
}


const LocoMotor::LMVector3& LocoMotor::Transform::GetPosition() {
	return _position;
}

const LocoMotor::LMVector3& LocoMotor::Transform::GetLocalPosition() {
	return _localPosition;
}

void LocoMotor::Transform::SetPosition(const LMVector3& newPosition) {
	//Sets Position In World Coordinates
	_position = newPosition;
	if (_gObjNode != nullptr){
		_gObjNode->SetPosition((float) newPosition.GetX(), (float) newPosition.GetY(), (float) newPosition.GetZ());
	}

	//Sets Position of Rigidbody
	SetPhysPosition(newPosition);
	////Sets Position of everychild
	if (childList.size() > 0) {
		for (auto a : childList){
			a->SetPosition(a->_localPosition + a->parent->GetPosition());
			//If has a Parent, recalculate LocalPosition j in case
			if(a->parent != nullptr) a->_localPosition = a->_position - a->parent->GetPosition();
		}
	}
}

void LocoMotor::Transform::SetLocalPosition(const LMVector3& newLocalPosition) {
	_localPosition = newLocalPosition;
}

//GETTERS
const LocoMotor::LMQuaternion& LocoMotor::Transform::GetRotation() {
	return _direction;}
const LocoMotor::LMQuaternion& LocoMotor::Transform::GetLocalRotation() {
	return _localDirection;}
const LocoMotor::LMVector3& LocoMotor::Transform::GetEulerRotation() {
	return _direction.ToEuler();}
const LocoMotor::LMVector3& LocoMotor::Transform::GetLocalEulerRotation() {
	return _localDirection.ToEuler();
}

//SET ROTATIONS
void LocoMotor::Transform::SetRotation(const LMVector3& newRotation) {
	SetRotation(newRotation.AsRotToQuaternion());
}

void LocoMotor::Transform::SetRotation(const LMQuaternion& newRotation) {
	_direction = newRotation;
	_direction.Normalize();
	if (_gObjNode != nullptr) {
		Ogre::Quaternion a = LmToOgre(newRotation);
		_gObjNode->SetOrientation(a);
	}
	SetPhysRotation(newRotation);
	//Set Rotation of EveryChild
	if (childList.size() > 0) {
		for (auto a : childList) {
			a->SetRotation(a->GetLocalRotation() + a->GetParent()->_direction);
		}
	}
}

void LocoMotor::Transform::SetLocalRotation(const LMVector3& newRotation) {
	SetLocalRotation(newRotation.AsRotToQuaternion());
}

void LocoMotor::Transform::SetLocalRotation(const LMQuaternion& newRotation) {
	_localDirection = newRotation;
	_localDirection.Normalize();
	if (_gObjNode != nullptr) {
		Ogre::Quaternion a = LmToOgre(_localDirection);
		_gObjNode->SetOrientation(a);
	}
	SetPhysRotation(newRotation);
}



const LocoMotor::LMVector3& LocoMotor::Transform::GetSize() {
	return _scale;
}

void LocoMotor::Transform::SetSize(const LMVector3& newSize) {
	_scale = newSize;
	if (_gObjNode != nullptr)
		_gObjNode->SetScale((float) newSize.GetX(), (float) newSize.GetY(), (float) newSize.GetZ());
	SetPhysScale(newSize);
}

void LocoMotor::Transform::SetUpwards(const LMVector3& newUpward) {
	double angle = GetRotation().Up().Angle(newUpward);
	if (angle == 0.) return;

	LMVector3 v1 = GetRotation().Up();
	LMVector3 v2 = newUpward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}


void LocoMotor::Transform::SetForward(const LMVector3& newForward) {
	double angle = GetRotation().Forward().Angle(newForward);
	if (angle == 0.) return;

	LMVector3 v1 = GetRotation().Forward();
	LMVector3 v2 = newForward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}


void LocoMotor::Transform::LookAt(const LMVector3& lookPos) {
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
}


void LocoMotor::Transform::LookAt(const LMVector3& lookPos, const LMVector3& up) {
	SetUpwards(up);
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
}

void LocoMotor::Transform::AddChild(Transform* trToAdd, bool resetLocal){
	childList.push_back(trToAdd);
	trToAdd->SetParent(this);
}

void LocoMotor::Transform::RemoveChild(Transform* trToRemove) {
	//childList.remove(trToRemove);
}

void LocoMotor::Transform::SetParent(Transform* trParent) {
	parent = trParent;
	_localPosition = _position - parent->GetPosition();
	_localDirection = _direction - parent->GetRotation();
	std::cout << "\nObjecto: " << this->gameObject->GetName() << " tiene Local a: " << _localPosition.ToString()<<"\n";
	std::cout << "\nObjecto: " << this->gameObject->GetName() << " tiene Rotation Local a: " << _localDirection.ToString()<<"\n";
}
const LocoMotor::Transform* LocoMotor::Transform::GetParent() {
	return parent;
}

void LocoMotor::Transform::SetPhysPosition(const LMVector3& newPosition) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->SetPosition(newPosition);
	}
}


void LocoMotor::Transform::SetPhysRotation(const LMQuaternion& newRotation) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->SetRotation(newRotation);
	}
}


void LocoMotor::Transform::SetPhysEulerRotation(const LMVector3& newRotation) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->SetRotation(newRotation.AsRotToQuaternion());
	}
}


void LocoMotor::Transform::SetPhysScale(const LMVector3& newsize) {
}
