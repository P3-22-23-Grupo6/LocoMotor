#pragma once
#ifndef LM_FACTORY_COMPONENT
#define LM_FACTORY_COMPONENT

#include "ComponentsFactory.h"
#include <string>

namespace LocoMotor {
	class Component;

	template <typename T>
	class FactoryComponent {
	public:
		FactoryComponent() {
			ComponentsFactory::GetInstance()->RegisterFactoryComponent(T::name, (CmpFactory) []() {
				return static_cast<Component*>(new T());
			});
		};
	};
}
#endif
