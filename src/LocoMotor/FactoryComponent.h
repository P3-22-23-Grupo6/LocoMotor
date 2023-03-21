#pragma once
#ifndef LM_FACTORY_COMPONENT
#define LM_FACTORY_COMPONENT

namespace LocoMotor {
	class Component;
	class FactoryComponent {
	public:
		/// @brief Constructor
		FactoryComponent() = default;
		/// @brief Destructor
		virtual ~FactoryComponent() = default;
		/// @brief Create a component
		virtual Component* Create();
	};
}
#endif
