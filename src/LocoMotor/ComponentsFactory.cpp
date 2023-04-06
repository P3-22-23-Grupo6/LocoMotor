#include "ComponentsFactory.h"
#include "FactoryComponent.h"

LocoMotor::ComponentsFactory* Singleton<LocoMotor::ComponentsFactory>::_instance = nullptr;

LocoMotor::ComponentsFactory::ComponentsFactory() {
}

LocoMotor::ComponentsFactory::~ComponentsFactory() {
	_factories.clear();
}

void LocoMotor::ComponentsFactory::RegisterFactoryComponent(const std::string& name, CmpFactory fac) {
	if (_factories[name] != nullptr) return;
	_factories[name] = fac;
}

LocoMotor::Component* LocoMotor::ComponentsFactory::CreateComponent(const std::string& name) {
	std::map<std::string, CmpFactory>::iterator it = _factories.find(name);
	if (it == _factories.end()) return nullptr;
	return it->second();
}
