#pragma once
#ifndef LM_COMPONENTS_FACTORY
#define LM_COMPONENTS_FACTORY
#include <map>
#include <string>
#include "Singleton.h"

namespace LocoMotor {
	class Component;

	typedef Component* (*CmpFactory) ();

	class ComponentsFactory : public Singleton<ComponentsFactory>{

		friend Singleton<ComponentsFactory>;

	public:
		/// @brief Destructor
		~ComponentsFactory();
		/// @brief Register a FactoryComponent by a name
		void RegisterFactoryComponent(const std::string& name, CmpFactory fac);
		/// @brief Create a Component
		Component* CreateComponent(const std::string& name);

		template <typename T>
		void RegisterComponent() {
			this->RegisterFactoryComponent(T::name, (CmpFactory) []() {
				return static_cast<Component*>(new T());
			});
		};
	protected:
		std::map<std::string, CmpFactory> _factories;
	private:
		/// @brief Constructor
		ComponentsFactory();
	};
}
#endif 
