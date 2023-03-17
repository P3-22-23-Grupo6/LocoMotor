#include "AudioSource.h"
#include "GameObject.h"
#include "LocoMotor_Utils/lmVector.h"
#include "LocoMotor_FMod/include/AudioSource.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace LocoMotor;
using namespace LM_Component;

AudioSource::AudioSource() {
	src = new FmodWrapper::AudioSource();
	lastError = 0;
}

AudioSource::~AudioSource() {
	delete src;
}

void LocoMotor::LM_Component::AudioSource::Update(float dt) {
#ifdef _DEBUG
	std::cout << src->GetManager()->GetError(lastError) << std::endl;
#endif // _DEBUG
	src->SetPositionAndVelocity(LMVector3::LmToFMod(ent->GetTransform().position), dt);
}

void LocoMotor::LM_Component::AudioSource::Play(const unsigned short id, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	lastError = src->PlaySound(id, loop, loopStart, loopEnd);
}

void LocoMotor::LM_Component::AudioSource::PauseSound(const unsigned int id, bool pause) {
	lastError = src->PauseS(id, pause);
}

void LocoMotor::LM_Component::AudioSource::Pause(bool pause) {
	lastError = src->PauseSource(pause);
}

void LocoMotor::LM_Component::AudioSource::Stop(const unsigned int id) {
	lastError = src->StopSound(id);
}

void LocoMotor::LM_Component::AudioSource::Stop() {
	lastError = src->StopSource();
}

void LocoMotor::LM_Component::AudioSource::SetVolume(const unsigned int id, const float volume) {
	lastError = src->SetSoundVolume(id, volume);
}

void LocoMotor::LM_Component::AudioSource::SetVolume(const float volume) {
	lastError = src->SetSourceVolume(volume);
}

void LocoMotor::LM_Component::AudioSource::SetFreq(const float freqMult) {
	lastError = src->SetFrequency(freqMult);
}

void LocoMotor::LM_Component::AudioSource::SetFreq(const unsigned short id, const float freqMult) {
	lastError = src->SetSoundFreq(id, freqMult);
}
