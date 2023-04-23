#include "AudioListener.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMVector.h"
#include "LocoMotor_FMod/include/AudioListener.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#include "LmVectorConverter.h"

using namespace LocoMotor;

const std::string AudioListener::name = "AudioListener";

AudioListener::AudioListener() {
	_list = nullptr;
	_lastPos = LMVector3();
	_lastVel = LMVector3();
}

AudioListener::~AudioListener() {
	delete _list;
}

void LocoMotor::AudioListener::Start() {
	_lastPos = gameObject->GetTransform()->GetPosition();
}

void LocoMotor::AudioListener::InitComponent() {
	_list = new FmodWrapper::AudioListener();
}

void LocoMotor::AudioListener::Update(float dt) {

	LMVector3 forwardVec = gameObject->GetTransform()->GetRotation().Forward() * -1;
	LMVector3 upwardVec = gameObject->GetTransform()->GetRotation().Up();

	LMVector3 vel = _lastVel + ((((gameObject->GetTransform()->GetPosition() - _lastPos) / (dt / 1000.f)) - _lastVel) * 0.9f);

#ifdef _DEBUG
	auto err = _list->SetTransform(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(vel), LmToFMod(forwardVec), LmToFMod(upwardVec));
	if (err > 0) {
		std::cout << "AudioListener::Update(): " << FmodWrapper::AudioManager::GetInstance()->GetError(err) << std::endl;
	}
#else
	_list->SetTransform(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(vel), LmToFMod(forwardVec), LmToFMod(upwardVec));
#endif // _DEBUG

	_lastPos = gameObject->GetTransform()->GetPosition();
	_lastVel = vel;
}


