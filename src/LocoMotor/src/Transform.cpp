#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderScene.h"
#include "RigidBody.h"
#include "Node.h"
#include "OgreManager.h"
#include "LmVectorConverter.h"


/**
 * The constructor for the Transform class initializes its member variables.
 */
LocoMotor::Transform::Transform() {
	_position = LMVector3();
	_direction = LMQuaternion();
	_scale = LMVector3(1, 1, 1);

	_gObjNode = nullptr;
}

LocoMotor::Transform::~Transform() {
}

/**
 * The function initializes a component for a game object and registers its transform.
 */
void LocoMotor::Transform::InitComponent() {
	gameObject->RegisterTransform(this);
	_gObjNode = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName())->GetNode(gameObject->GetName());
}

/**
 * This function initializes the position, rotation, and scale of a game object's transform based on
 * input parameters.
 * @brief Initializes the position, rotation, and scale of a game object's transform based on input parameters.
 * @param params A vector of pairs, where each pair contains a string representing a parameter name and
 * a string representing the value of that parameter. The function uses these parameters to initialize
 * the position, rotation, and scale of a transform component.
 */
void LocoMotor::Transform::Init(std::vector<std::pair<std::string, std::string>>& params) {
	gameObject->RegisterTransform(this);
	_gObjNode = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName())->GetNode(gameObject->GetName());
	//TODO: como coooo
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
			SetLocalPosition(result);
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
			SetLocalEulerRotation(result);
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
			SetLocalScale(result);
		}
	}
}

void LocoMotor::Transform::Start() {
}

void LocoMotor::Transform::Update(const float dt) {
}

/**
 * The function returns the local position of the LocoMotor object.
 * @brief Returns the local position of the LocoMotor object.
*/
const LocoMotor::LMVector3& LocoMotor::Transform::GetPosition() {
	return _position;
}

/**
 * The function sets the position of the LocoMotor object.
 * @brief Sets the position of the LocoMotor object.
 * @param newPosition 
 */
void LocoMotor::Transform::SetPosition(const LMVector3& newPosition) {
	SetLocalPosition(newPosition);
	SetPhysPosition(newPosition);
}

/**
 * The function returns the rotation of the LocoMotor object. 
 * @brief Returns the rotation of the LocoMotor object.
*/
const LocoMotor::LMQuaternion& LocoMotor::Transform::GetRotation() {
	return _direction;
}

/**
 * The function sets the rotation of the LocoMotor object.
 * @brief Sets the rotation of the LocoMotor object.
 * @param newRotation 
 */
void LocoMotor::Transform::SetRotation(const LMQuaternion& newRotation) {
	SetLocalRotation(newRotation);
	SetPhysRotation(newRotation);
}

/**
 * The function returns the position of the LocoMotor object. 
 * @brief Returns the position of the LocoMotor object.
*/
const LocoMotor::LMVector3& LocoMotor::Transform::GetEulerRotation() {
	return _directionEuler;
}

/**
 * The function sets the rotation of the LocoMotor object.
 * @brief Sets the rotation of the LocoMotor object.
 * @param newRotation 
 */
void LocoMotor::Transform::SetEulerRotation(const LMVector3& newRotation) {
	SetLocalEulerRotation(newRotation);
	SetPhysEulerRotation(newRotation);
}

/*
 * The function returns the size of the LocoMotor object. 
 * @brief Returns the size of the LocoMotor object.
*/
const LocoMotor::LMVector3& LocoMotor::Transform::GetSize() {
	return _scale;
}

/**
 * The function sets the size of the LocoMotor object.
 * @brief Sets the size of the LocoMotor object.
 * @param newSize A LMVector3 representing the new size to set for the LocoMotor object.
 */
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

/**
 * The function sets up a new upward direction for a LocoMotor object by calculating the rotation
 * needed to align the current upward direction with the new one.
 * @brief Sets up a new upward direction for a LocoMotor object.
 * @param newUpward A LMVector3 representing the new upward direction to set for the LocoMotor object.
 * 
 * @return If the angle between the current upward vector and the new upward vector is 0, then nothing
 * is done and the function returns without making any changes.
 */
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

/**
 * The function sets the forward direction of a LocoMotor object by calculating the rotation needed to
 * align the current forward direction with a new given direction.
 * @brief Sets the forward direction of a LocoMotor object.
 * @param newForward A LMVector3 representing the new forward direction that the LocoMotor should face.
 * 
 * @return If the angle between the current forward vector and the new forward vector is 0, then
 * nothing is being returned (the function exits early with a return statement). Otherwise, the
 * function sets a new rotation based on the angle and axis calculated using the cross product of the
 * current forward vector and the new forward vector, but it does not explicitly return anything.
 */
void LocoMotor::Transform::SetForward(const LMVector3& newForward) {
	double angle = GetRotation().Forward().Angle(newForward);
	if (angle == 0.) return;


	//LMVector3 axis = GetRotation().Up() * newUpward;
	// Producto vectorial para hallar el vector perpendicular a otros dos vectores
	// Despues pasar esto al LMVectoresque :TODO

	LMVector3 v1 = GetRotation().Forward();
	LMVector3 v2 = newForward;
	LMVector3 axis = LMVector3(
		v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
		v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
		v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());

	SetRotation(GetRotation().Rotate(axis, angle));
}

/**
 * The function updates the forward vector of a LocoMotor object to face towards a given position.
 * @brief Updates the forward vector of a LocoMotor object.
 * @param lookPos A LMVector3 representing the position to look at.
 */
void LocoMotor::Transform::LookAt(const LMVector3& lookPos) {
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
	//_gObjNode->LookAt(lookPos.GetX() * 10, lookPos.GetY() * 10, lookPos.GetZ() * 10);
}

/**
 * The function sets the forward and upward vectors of a transform to look at a specified position with
 * a specified upward direction.
 * 
 * @param lookPos A LMVector3 representing the position that the LocoMotor's Transform should be
 * looking at.
 * @param up The "up" parameter is a LMVector3 that represents the direction that is considered "up" in
 * the world space. This is used to ensure that the object being transformed maintains a consistent
 * orientation, even if it is rotated.
 */
void LocoMotor::Transform::LookAt(const LMVector3& lookPos, const LMVector3& up) {
	SetUpwards(up);
	LMVector3 newForward = lookPos - GetPosition();
	SetForward(newForward);
}

/**
 * This function sets the local position of a transform and updates the position of the corresponding
 * game object node.
 * @brief Sets the local position of a transform.
 * @param newPosition newPosition is a constant reference to an LMVector3 object, which represents the
 * new local position that we want to set for the LocoMotor object.
 */
void LocoMotor::Transform::SetLocalPosition(const LMVector3& newPosition) {
	_position = newPosition;
	_gObjNode->SetPosition((float)newPosition.GetX(), (float) newPosition.GetY(), (float) newPosition.GetZ());
}

/**
 * This function sets the local rotation of a LocoMotor object and updates its corresponding Ogre node.
 * @brief Sets the local rotation of a LocoMotor object.
 * @param newRotation A LMQuaternion object representing the new rotation to be set for the LocoMotor's
 * Transform.
 */
void LocoMotor::Transform::SetLocalRotation(const LMQuaternion& newRotation) {
	_direction = newRotation;
	_direction.Normalize();
	Ogre::Quaternion a = LmToOgre(newRotation);
	_gObjNode->SetOrientation(a);
	_directionEuler = _direction.ToEuler();
}

/**
 * This function sets the local Euler rotation of a LocoMotor object and updates its orientation in an
 * Ogre scene.
 * @brief Sets the local Euler rotation of a LocoMotor object.
 * @param newRotation A LMVector3 object representing the new rotation to be set in local Euler angles.
 */
void LocoMotor::Transform::SetLocalEulerRotation(const LMVector3& newRotation) {
	_direction = newRotation.AsRotToQuaternion();
	_direction.Normalize();
	Ogre::Quaternion a = LmToOgre(newRotation.AsRotToQuaternion());
	_gObjNode->SetOrientation(a);
	_directionEuler = newRotation;
}

/**
 * This function sets the local scale of a transform and updates the scale of the corresponding game
 * object node.
 * @brief Sets the local scale of a transform.
 * @param newSize newSize is a reference to an LMVector3 object, which represents the new scale of the
 * object. It contains three float values representing the new scale along the x, y, and z axes.
 */
void LocoMotor::Transform::SetLocalScale(const LMVector3& newSize) {
	_scale = newSize;
	_gObjNode->SetScale((float)newSize.GetX(), (float)newSize.GetY(), (float)newSize.GetZ());
}

/**
 * This function sets the physical position of a game object with a rigid body component.
 * @brief Sets the physical position of a game object with a rigid body component.
 * @param newPosition A constant reference to an LMVector3 object representing the new physical
 * position to set for the LocoMotor object.
 */
void LocoMotor::Transform::SetPhysPosition(const LMVector3& newPosition) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->setPosition(newPosition);
	}
}

/**
 * This function sets the physical rotation of a game object with a rigid body component to a new
 * quaternion value.
 * @brief Sets the physical rotation of a game object with a rigid body component.
 * @param newRotation The new rotation that the function is setting for the physics object. It is of
 * type LMQuaternion, which is likely a custom quaternion class specific to the game engine or
 * framework being used.
 */
void LocoMotor::Transform::SetPhysRotation(const LMQuaternion& newRotation) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->setRotation(newRotation);
	}
}

/**
 * This function sets the physical Euler rotation of a game object's rigid body component.
 * @brief Sets the physical Euler rotation of a game object's rigid body component.
 * @param newRotation A LMVector3 object representing the new rotation to be set for the Transform.
 */
void LocoMotor::Transform::SetPhysEulerRotation(const LMVector3& newRotation) {
	RigidBody* rb = gameObject->GetComponent<RigidBody>();
	if (rb != nullptr) {
		rb->setRotation(newRotation.AsRotToQuaternion());
	}
}

//TODO: cabron
void LocoMotor::Transform::SetPhysScale(const LMVector3& newsize) {
}


