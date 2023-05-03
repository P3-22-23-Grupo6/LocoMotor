#pragma once
#ifndef LM_COMPONENTS_FACTORY
#define LM_COMPONENTS_FACTORY
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <map>
#include <string>
#include "Singleton.h"

namespace LocoMotor {
	class Component;

	typedef Component* (*CmpFactory) ();

	class MOTOR_API ComponentsFactory : public Singleton<ComponentsFactory> {

		friend Singleton<ComponentsFactory>;

	public:
		/// @brief Destructor
		~ComponentsFactory();
		/// @brief Register a FactoryComponent by a name
		void RegisterFactoryComponent(const std::string& name, CmpFactory fac);
		/// @brief Create a Component
		Component* CreateComponent(const std::string& name);
		/// @brief Register the component to the factory
		/// @tparam T The component Typek
		/// @param name The name to save and uses when creates the component
		template <typename T>
		void RegisterComponent(std::string name) {
			this->RegisterFactoryComponent(name, (CmpFactory) []() {
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
