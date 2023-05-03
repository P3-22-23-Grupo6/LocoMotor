#include "GameObject.h"
#include "Transform.h"

//HITO 1 POC
#include "InputManager.h"
#include "LMInputs.h"
#include "Scene.h"
#include "Node.h"
//Borrar luego
#include "SceneManager.h"
#include "RigidBodyComponent.h"
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
	/*this->AddComponent("Transform");*/
	tiltAmount = 0.0f; //TEMPORAL
}

// Update the GameObject
void GameObject::Update(float dt) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->PreUpdate(dt);
	}
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->Update(dt);
	}


	//if (GetComponent<RigidBodyComponent>() == nullptr) return;
	//InputManager* man = InputManager::GetInstance();


	if (!movable)return;

	RigidBodyComponent* rbComp = GetComponent<RigidBodyComponent>();
}


/**
 * This function adds a component to a game object and sets its context and parameters.
 * @brief Adds a component to a game object and sets its context and parameters.
 * @param name A string representing the name of the component to be added to the GameObject.
 * @param params params is a vector of pairs of strings that represent the parameters needed to
 * initialize a component. The first string in each pair is the name of the parameter, and the second
 * string is the value of the parameter. These parameters are used to initialize the component created
 * by the ComponentsFactory.
 * 
 * @return If the component with the given name already exists in the `_componentsByName` map, nothing
 * is done and the function returns without any value.
 */
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


/**
 * The function iterates through all enabled components of a game object and calls their
 * OnCollisionEnter function with a given game object as a parameter when a collision occurs.
 * @brief Calls the OnCollisionEnter function of all enabled components when entering a collision.
 * @param other The "other" parameter is a pointer to another GameObject that this GameObject has
 * collided with.
 */
void LocoMotor::GameObject::OnCollisionEnter(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionEnter(other);
	}
}

/**
 * The function iterates through all enabled components of a game object and calls their
 * OnCollisionExit function with a given game object as a parameter when a collision ends.
 * @brief Calls the OnCollisionExit function of all enabled components when exiting a collision.
 * @param other The "other" parameter is a pointer to another GameObject that this GameObject has
 * collided with.
 */
void LocoMotor::GameObject::OnCollisionExit(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionExit(other);
	}
}

/**
 * The function iterates through all enabled components of a game object and calls their
 * OnCollisionStay function with a given game object as a parameter when a collision is ongoing.
 * @brief Calls the OnCollisionStay function of all enabled components when a collision is ongoing.
 * @param other The "other" parameter is a pointer to another GameObject that this GameObject has
 * collided with.
 */
void LocoMotor::GameObject::OnCollisionStay(GameObject* other) {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it++) {
		if (it->second->isEnabled())
			it->second->OnCollisionStay(other);
	}
}


/**
 * This function sets the position of a game object using a given LMVector3 position.
 * @brief Sets the position of a game object using a given LMVector3 position.
 * @param pos pos is a LMVector3 variable that represents the new position of the GameObject. It is
 * passed as a parameter to the SetPosition function of the GameObject class. The function then sets
 * the position of the GameObject's transform component to the new position.
 */
void GameObject::SetPosition(LMVector3 pos) {
	transform->SetPosition(pos);
}

/**
 * This function sets the rotation of a game object using a given quaternion.
 * @brief Sets the rotation of a game object using a given quaternion.
 * @param rot The parameter "rot" is of type LMQuaternion, which is likely a custom data type defined
 * in the codebase. It is being passed as an argument to the SetRotation() function of the transform
 * component of a GameObject. This function is likely used to set the rotation of the GameObject in 3
 */
void LocoMotor::GameObject::SetRotation(LMQuaternion rot) {
	transform->SetRotation(rot);
}


/**
 * This function sets the scale of a game object using a given vector.
 * @brief Sets the scale of a game object using a given vector.
 * @param sc A LMVector3 variable representing the scale of the GameObject. This function sets the size
 * of the transform component of the GameObject to the specified scale.
 */
void GameObject::SetScale(LMVector3 sc) {
	transform->SetSize(sc);
}


/**
 * The function returns the transform component of a game object.
 * @brief Returns the transform component of a game object.
 * @return A pointer to the Transform component of the GameObject.
 */
Transform* GameObject::GetTransform() {
	return transform;
}

/**
 * This function returns the name of a game object's node.
 * @brief Returns the name of a game object's node.
 * @return A string representing the name of the game object's node.
 */
std::string LocoMotor::GameObject::GetName() {
	return _node->GetName();
}


/**
 * This function sets the renderer for a game object using an OgreWrapper node.
 * @brief Sets the renderer for a game object using an OgreWrapper node.
 * @param node The parameter "node" is a pointer to an object of type "OgreWrapper::Node". This object
 * is likely a node in a scene graph that represents a visual component of a game object. The
 * "SetRenderer" function is likely used to associate this visual component with the game object so
 * that
 */
void LocoMotor::GameObject::SetRenderer(OgreWrapper::Node* node) {
	_node = node;
}

/**
 * This function sets the context of a GameObject to a specific Scene.
 * @brief Sets the context of a GameObject to a specific Scene.
 * @param scn A pointer to a Scene object, which is being passed as a parameter to the SetContext()
 * function of the GameObject class. The function sets the value of the "scene" member variable of the
 * GameObject class to the value of the "scn" parameter. This allows the GameObject to access and
 * interact
 */
void LocoMotor::GameObject::SetContext(Scene* scn) {
	scene = scn;
}

/**
 * The function returns the scene of a game object in C++.
 * @brief Returns the scene of a game object in C++.
 * @return A pointer to a Scene object.
 */
Scene* LocoMotor::GameObject::GetScene() {
	return scene;
}

/**
 * This function starts the components of a game object.
 * @brief starts the components of a game object.
 */
void GameObject::StartComp() {
	for (auto& comp : _componentsByName) {
		comp.second->PreStart();
	}
	for (auto& comp : _componentsByName) {
		comp.second->Start();
	}
}

/**
 * The function sets the transform of a GameObject to a new Transform object.
 * @brief Sets the transform of a GameObject to a new Transform object.
 * @param newTrans A pointer to a Transform object that is being registered to the GameObject.
 */
void LocoMotor::GameObject::RegisterTransform(Transform* newTrans) {
	transform = newTrans;
}


// Destructor
GameObject::~GameObject() {
	std::unordered_map<std::string, Component*>::iterator it;
	for (it = _componentsByName.begin(); it != _componentsByName.end(); it = _componentsByName.erase(it)) {
		delete it->second;
	}
}