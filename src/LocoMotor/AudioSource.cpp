#include "AudioSource.h"
#include "GameObject.h"
#include "LocoMotor_Utils/lmVector.h"
#include "LocoMotor_FMod/include/AudioSource.h"

using namespace LocoMotor;
using namespace Component;

AudioSource::AudioSource() {
	src = new FmodWrapper::AudioSource();
}

void LocoMotor::Component::AudioSource::Update(float dt) {
	src->SetPositionAndVelocity(LMVector3::LmToFMod(ent->GetTransform().position), dt);
}

void LocoMotor::Component::AudioSource::PlaySound(const unsigned short id, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	src->PlaySound(id, loop, loopStart, loopEnd);
}
