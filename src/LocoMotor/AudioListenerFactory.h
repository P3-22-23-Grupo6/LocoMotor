#pragma once
#ifndef LM_AUDIOLISTENER_FACTORY
#define LM_AUDIOLISTENER_FACTORY

#include "FactoryComponent.h"

namespace LocoMotor {
	class AudioListenerFactory :public FactoryComponent {
	public:
		AudioListenerFactory();
		~AudioListenerFactory();
		Component* Create(std::vector<std::pair<std::string, std::string>>& params)override;
	};
}


#endif // !LM_AUDIOLISTENER_FACTORY

