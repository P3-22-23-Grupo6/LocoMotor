#include "AudioSourceFactory.h"
#include "AudioSource.h"

using namespace LocoMotor;

LocoMotor::AudioSourceFactory::AudioSourceFactory() {
}

LocoMotor::AudioSourceFactory::~AudioSourceFactory() {
}

Component* LocoMotor::AudioSourceFactory::Create(std::string params) {
	return new AudioSource();
}
