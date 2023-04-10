#include "AudioSource.h"
#include "GameObject.h"
#include "LMVector.h"
#include "LocoMotor_FMod/include/AudioSource.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <LogSystem.h>


using namespace LocoMotor;

const std::string AudioSource::name = "AudioSource";

AudioSource::AudioSource() {
	_src = new FmodWrapper::AudioSource();
	_lastError = 0;
}

AudioSource::~AudioSource() {
	delete _src;
}

void LocoMotor::AudioSource::Update(float dt) {
#ifdef _DEBUG
	if (_lastError != 0)
		std::cout << FmodWrapper::AudioManager::GetInstance()->GetError(_lastError) << std::endl;
#endif // _DEBUG
	_src->SetPositionAndVelocity(LMVector3::LmToFMod(gameObject->GetTransform().position), dt / 1000.f);
}

void LocoMotor::AudioSource::Play(const char* fileName, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	_lastError = _src->PlaySound(fileName, loop, loopStart, loopEnd);
}

void LocoMotor::AudioSource::PauseSound(const char* fileName, bool pause) {
	_lastError = _src->PauseS(fileName, pause);
}

void LocoMotor::AudioSource::Pause(bool pause) {
	_lastError = _src->PauseSource(pause);
}

void LocoMotor::AudioSource::Stop(const char* fileName) {
	_lastError = _src->StopSound(fileName);
}

void LocoMotor::AudioSource::Stop() {
	_lastError = _src->StopSource();
}

void LocoMotor::AudioSource::SetVolume(const char* fileName, const float volume) {
	_lastError = _src->SetSoundVolume(fileName, volume);
}

void LocoMotor::AudioSource::SetVolume(const float volume) {
	_lastError = _src->SetSourceVolume(volume);
}

void LocoMotor::AudioSource::SetFreq(const char* fileName, const float freqMult) {
	_lastError = _src->SetSoundFreq(fileName, freqMult);
}

void LocoMotor::AudioSource::SetFreq(const float freqMult) {
	_lastError = _src->SetFrequency(freqMult);
}
