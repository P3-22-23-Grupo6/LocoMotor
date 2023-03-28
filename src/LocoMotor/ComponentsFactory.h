#pragma once
#ifndef LM_COMPONENTS_FACTORY
#define LM_COMPONENTS_FACTORY
#include <map>
#include <string>

namespace LocoMotor {
	class Component;
	class FactoryComponent;
	class ComponentsFactory {
	public:
		/// @brief Constructor
		ComponentsFactory();
		/// @brief Destructor
		~ComponentsFactory();
		/// @brief Register a FactoryComponent by a name
		void RegisterFactoryComponent(std::string name, FactoryComponent* factComp);
		/// @brief Create a Component
		Component* CreateComponent(std::string name, std::string params);
	protected:
		std::map<std::string, FactoryComponent*> _factories;
	};
}
#endif 
