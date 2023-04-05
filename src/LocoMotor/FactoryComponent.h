#pragma once
#ifndef LM_FACTORY_COMPONENT
#define LM_FACTORY_COMPONENT
#include <string>
#include <vector>
namespace LocoMotor {
	class Component;
	class FactoryComponent {
	public:
		/// @brief Constructor
		FactoryComponent() = default;
		/// @brief Destructor
		virtual ~FactoryComponent() = default;
		/// @brief Create a component
		virtual Component* Create(std::vector<std::pair<std::string, std::string>>& params);
	};
}
#endif
