#include "Component.h"
#include "GameObject.h"


/**
 * The function returns the game object context of a component in a C++ program.
 * @brief Returns the game object context of a component in a C++ program.
 * @return A pointer to a GameObject object, which is the context of the Component object.
 */
LocoMotor::GameObject* LocoMotor::Component::GetContext() {
	return gameObject;
}
/**
 * The function sets the context of a LocoMotor component to a specific game object.
 * @brief Sets the context of a LocoMotor component to a specific game object.
 * @param ent ent is a pointer to a GameObject, which is being passed as a parameter to the SetContext
 * function of the Component class. The function sets the gameObject member variable of the Component
 * class to the value of the ent parameter.
 */
void LocoMotor::Component::SetContext(GameObject* ent) {
	this->gameObject = ent;
}

/**
 * This function sets the active state of a locomotor component and calls the appropriate
 * enable/disable function.
 * @brief Sets the active state of a locomotor component and calls the appropriate enable/disable function.
 * @param active a boolean value indicating whether the component should be set as active or inactive.
 */
void LocoMotor::Component::SetActive(bool active) {
	if (active && !enabled) {
		enabled = active;
		OnEnable();
	}
	else if (!active && enabled) {
		enabled = active;
		OnDisable();
	}
}

/**
 * The function returns a boolean value indicating whether the LocoMotor component is enabled or not.
 * @brief Returns a boolean value indicating whether the LocoMotor component is enabled or not.
 * @return the value of the boolean variable "enabled".
 */
bool LocoMotor::Component::isEnabled() {
	return enabled;
}

/**
 * This is the constructor for the Component class in the LocoMotor namespace, which initializes the
 * gameObject pointer to nullptr and sets the enabled flag to true.
 */
LocoMotor::Component::Component()
{
	gameObject = nullptr;
	enabled = true;
}
