#include "AudioSource.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMVector.h"
#include "LocoMotor_FMod/include/AudioSource.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#include "LmVectorConverter.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <LogSystem.h>


using namespace LocoMotor;

/**
 * This is the constructor for the AudioSource class, which initializes the _lastError variable to 0
 * and sets the _src pointer to nullptr.
 */
AudioSource::AudioSource() {
	_lastError = 0;
	_src = nullptr;
	_startPlay = "";
	_loops = 0;
	_loopStart = 0;
	_loopEnd = 0xffffffff;
}

/**
 * This is a destructor for the AudioSource class that deletes the _src object.
 */
AudioSource::~AudioSource() {
	delete _src;
}


void LocoMotor::AudioSource::InitComponent() {
	_src = new FmodWrapper::AudioSource();
}


void LocoMotor::AudioSource::Init(std::vector<std::pair<std::string, std::string>>& params) {
	_src = new FmodWrapper::AudioSource();
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "vol" || params[i].first == "volume") {
			float num = 1.f;
			try {
				num = std::stof(params[i].second);
			}
			catch (...) {
				num = 1.f;
			}
			SetVolume(num);
		}
		else if (params[i].first == "freq" || params[i].first == "frequency") {
			float num = 1.f;
			try {
				num = std::stof(params[i].second);
			}
			catch (...) {
				num = 1.f;
			}
			SetFreq(num);
		}
		else if (params[i].first == "preloadaudio" || params[i].first == "loadaudio" || params[i].first == "load") {
			_src->AddSound(params[i].second.c_str());
		}
		else if (params[i].first == "loops") {
			int num = 1;
			try {
				num = std::stoi(params[i].second);
			}
			catch (...) {
				num = 1;
			}
			_loops = num;
		}
		else if (params[i].first == "loopStart") {
			int num = 0;
			try {
				num = std::stoi(params[i].second);
			}
			catch (...) {
				num = 0;
			}
			if (num < 0)
				num = 0;
			_loopStart = num;
		}
		else if (params[i].first == "loopEnd") {
			int num = 0;
			try {
				num = std::stoi(params[i].second);
			}
			catch (...) {
				num = 0;
			}
			if (num < 0)
				num = 0;
			_loopEnd = num;
		}
		else if (params[i].first == "playonStart") {
			_startPlay = params[i].second;
		}
		else if (params[i].first == "soundDimension") {
			if (params[i].second == "2D")
				Set2D();
			else if (params[i].second == "3D")
				Set3D();
			else
				Set3D();
		}
	}
}

void LocoMotor::AudioSource::PreStart() {
}

void LocoMotor::AudioSource::Start() {
	_src->SetPositionAndVelocity(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(LMVector3()));
	if (_startPlay != "")
		Play(_startPlay.c_str(), _loops, _loopStart, _loopEnd);
}


void LocoMotor::AudioSource::Update(float dt) {
#ifdef _DEBUG
	if (_lastError != 0) {
		std::cout << FmodWrapper::AudioManager::GetInstance()->GetError(_lastError) << std::endl;
		_lastError = 0;
	}
#endif // _DEBUG
	_src->SetPositionAndVelocity(LmToFMod(gameObject->GetTransform()->GetPosition()), dt / 1000.f);
}


void LocoMotor::AudioSource::Play(const char* fileName, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	_lastError = _src->PlaySound(fileName, loop, loopStart, loopEnd);
}


void LocoMotor::AudioSource::PlayOneShot(const char* fileName, const LMVector3& position, const float volume) {
	_lastError = _src->PlayOneShot(fileName, LmToFMod(position), volume);
}


void LocoMotor::AudioSource::PlayOneShot(const char* fileName, const LMVector3& position, const float volume, const float pitch) {
	_lastError = _src->PlayOneShot(fileName, LmToFMod(position), volume, pitch);
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



void LocoMotor::AudioSource::Set3D() {
	_src->SetMode3D();
}


void LocoMotor::AudioSource::Set2D() {
	_src->SetMode2D();
}
