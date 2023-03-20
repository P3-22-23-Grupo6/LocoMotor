#include "AudioSource.h"
#include "GameObject.h"
#include "LocoMotor_Utils/lmVector.h"
#include "LocoMotor_FMod/include/AudioSource.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace LocoMotor;

AudioSource::AudioSource() {
	_src = new FmodWrapper::AudioSource();
	_lastError = 0;
}

AudioSource::~AudioSource() {
	delete _src;
}

void LocoMotor::AudioSource::Update(float dt) {
#ifdef _DEBUG
	std::cout << FmodWrapper::AudioManager::GetInstance()->GetError(_lastError) << std::endl;
#endif // _DEBUG
	_src->SetPositionAndVelocity(LMVector3::LmToFMod(ent->GetTransform().position), dt);
}

void LocoMotor::AudioSource::Play(const unsigned short id, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	_lastError = _src->PlaySound(id, loop, loopStart, loopEnd);
}

void LocoMotor::AudioSource::PauseSound(const unsigned int id, bool pause) {
	_lastError = _src->PauseS(id, pause);
}

void LocoMotor::AudioSource::Pause(bool pause) {
	_lastError = _src->PauseSource(pause);
}

void LocoMotor::AudioSource::Stop(const unsigned int id) {
	_lastError = _src->StopSound(id);
}

void LocoMotor::AudioSource::Stop() {
	_lastError = _src->StopSource();
}

void LocoMotor::AudioSource::SetVolume(const unsigned int id, const float volume) {
	_lastError = _src->SetSoundVolume(id, volume);
}

void LocoMotor::AudioSource::SetVolume(const float volume) {
	_lastError = _src->SetSourceVolume(volume);
}

void LocoMotor::AudioSource::SetFreq(const float freqMult) {
	_lastError = _src->SetFrequency(freqMult);
}

void LocoMotor::AudioSource::SetFreq(const unsigned short id, const float freqMult) {
	_lastError = _src->SetSoundFreq(id, freqMult);
}
