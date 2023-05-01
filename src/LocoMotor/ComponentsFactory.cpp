#include "ComponentsFactory.h"

/* This line of code is defining a static member variable `_instance` of the
`LocoMotor::Singleton<LocoMotor::ComponentsFactory>` class template. It is initialized to `nullptr`,
which means that it does not point to any object yet. This variable is used to store the single
instance of the `LocoMotor::ComponentsFactory` class that is created by the `LocoMotor::Singleton`
template. */
LocoMotor::ComponentsFactory* LocoMotor::Singleton<LocoMotor::ComponentsFactory>::_instance = nullptr;

LocoMotor::ComponentsFactory::ComponentsFactory() {
}

LocoMotor::ComponentsFactory::~ComponentsFactory() {
	_factories.clear();
}

/**
 * This function registers a factory component with a given name and factory function.
 * @brief Registers a factory component with a given name and factory function.
 * @param name A string representing the name of the component factory being registered.
 * @param fac fac is a function pointer to a factory function that creates a component object. The
 * function takes no arguments and returns a pointer to the created component object.
 * 
 * @return If the condition in the if statement is true (i.e. the factory with the given name already
 * exists), then nothing is returned and the function exits early. If the condition is false (i.e. the
 * factory with the given name does not exist), then nothing is returned and the new factory is
 * registered in the _factories map.
 */
void LocoMotor::ComponentsFactory::RegisterFactoryComponent(const std::string& name, CmpFactory fac) {
	if (_factories[name] != nullptr) return;
	_factories[name] = fac;
}

/**
 * This function creates a component based on the given name by searching for a corresponding factory
 * in a map.
 * @brief Creates a component based on the given name by searching for a corresponding factory in a map.
 * @param name A string representing the name of the component to be created.
 * 
 * @return The function `CreateComponent` returns a pointer to a `LocoMotor::Component` object, which
 * is created by calling the appropriate factory function based on the input `name` parameter. If the
 * `name` parameter does not match any registered factory, the function returns a `nullptr`.
 */
LocoMotor::Component* LocoMotor::ComponentsFactory::CreateComponent(const std::string& name) {
	std::map<std::string, CmpFactory>::iterator it = _factories.find(name);
	if (it == _factories.end()) return nullptr;
	return it->second();
}
