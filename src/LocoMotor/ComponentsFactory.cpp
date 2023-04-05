#include "ComponentsFactory.h"
#include "FactoryComponent.h"


LocoMotor::ComponentsFactory::ComponentsFactory() {
}

LocoMotor::ComponentsFactory::~ComponentsFactory() {
	_factories.clear();
}

void LocoMotor::ComponentsFactory::RegisterFactoryComponent(std::string name, FactoryComponent* factComp) {
	_factories.insert(std::pair<std::string, FactoryComponent*>(name, factComp));
}

LocoMotor::Component* LocoMotor::ComponentsFactory::CreateComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params) {
	std::map<std::string, FactoryComponent*>::iterator it = _factories.find(name);
	if (it == _factories.end())return nullptr;
	return it->second->Create(params);
}
