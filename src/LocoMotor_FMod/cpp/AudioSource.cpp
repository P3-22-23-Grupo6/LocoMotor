#include "AudioSource.h"
#include "AudioManager.h"

AudioSource::~AudioSource () {
}

uint16_t AudioSource::AddSound (const uint32_t id, const char* fileName) {
	return _man->AddSound(id, fileName);
}

uint16_t AudioSource::PlaySound (const uint32_t id) {
	return 0;
}

void AudioSource::SetPosition (const LMVector3& newPos, bool updateVelocity) {
}

void AudioSource::SetVelocity (const LMVector3& newVel) {
}
