#include "AudioListenerFactory.h"
#include "AudioListener.h"

using namespace LocoMotor;

LocoMotor::AudioListenerFactory::AudioListenerFactory() {
}

LocoMotor::AudioListenerFactory::~AudioListenerFactory() {
}

Component* LocoMotor::AudioListenerFactory::Create(std::string params) {
	return new AudioListener();
}
