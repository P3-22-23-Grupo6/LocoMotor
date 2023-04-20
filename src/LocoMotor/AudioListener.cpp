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
	_lastPos = nullptr;
}

AudioListener::~AudioListener() {
	delete _list;
	delete _lastPos;
}

void LocoMotor::AudioListener::Start() {
	*_lastPos = gameObject->GetTransform()->GetPosition();
}

void LocoMotor::AudioListener::InitComponent() {
	_list = new FmodWrapper::AudioListener();
	_lastPos = new LMVector3();
}

void LocoMotor::AudioListener::Update(float dt) {

	LMVector3 forwardVec = gameObject->GetTransform()->GetRotation().Forward() * -1;
	LMVector3 upwardVec = gameObject->GetTransform()->GetRotation().Up();

	LMVector3 vel = (gameObject->GetTransform()->GetPosition() - *_lastPos) / (dt / 1000);

#ifdef _DEBUG
	auto err = _list->SetTransform(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(vel), LmToFMod(forwardVec), LmToFMod(upwardVec));
	if (err > 0) {
		std::cout << "AudioListener::Update(): " << FmodWrapper::AudioManager::GetInstance()->GetError(err) << std::endl;
	}
#else
	_list->SetTransform(gameObject->GetTransform()->GetPosition(), vel, forwardVec, LMVector3::LmToFMod(upwardVec));
#endif // _DEBUG

	*_lastPos = gameObject->GetTransform()->GetPosition();
}


