#pragma once
#ifndef LM_AUDIOSOURCE_FACTORY
#define LM_AUDIOSOURCE_FACTORY

#include "FactoryComponent.h"

namespace LocoMotor {
	class AudioSourceFactory:public FactoryComponent {
	public:
		AudioSourceFactory();
		~AudioSourceFactory();
		Component* Create(std::vector<std::pair<std::string, std::string>>& params)override;
	};
}
#endif // !LM_AUDIOSOURCE_FACTORY




