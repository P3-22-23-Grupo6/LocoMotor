#include "AudioListener.h"
#include "GameObject.h"
#include "LocoMotor_Utils/lmVector.h"
#include "LocoMotor_FMod/include/AudioListener.h"
#include "LocoMotor_FMod/include/AudioManager.h"

using namespace LocoMotor;

const std::string AudioListener::name = "AudioListener";

AudioListener::AudioListener() {
	_list = new FmodWrapper::AudioListener();
	_lastPos = new LMVector3();
}

AudioListener::~AudioListener() {
	delete _list;
	delete _lastPos;
}

void LocoMotor::AudioListener::Update(float dt) {
	double degToRad = 0.0174533;

	LMVector3 rot = gameObject->GetTransform().rotation * degToRad;
	LMVector3 forwardVec = LMVector3(std::sin(rot.GetY()) * std::cos(rot.GetX()),
									 std::sin(-rot.GetX()),
									 std::cos(rot.GetX()) * std::cos(rot.GetY()));

	// TODO: No se si este esta bien calculado pero bueno xd
	LMVector3 upwardVec = LMVector3(std::sin(-rot.GetZ()),
									std::cos(rot.GetX()) * std::cos(rot.GetZ()),
									std::sin(rot.GetZ()) * std::cos(rot.GetX()));

	LMVector3 vel = (gameObject->GetTransform().position - *_lastPos) / dt;

#ifdef _DEBUG
	std::cout << "AudioListener::Update(): " << FmodWrapper::AudioManager::GetInstance()->GetError(_list->SetTransform(LMVector3::LmToFMod(gameObject->GetTransform().position), LMVector3::LmToFMod(vel), LMVector3::LmToFMod(forwardVec), LMVector3::LmToFMod(upwardVec))) << std::endl;
#else
	_list->SetTransform(LMVector3::LmToFMod(ent->GetTransform().position), LMVector3::LmToFMod(vel), LMVector3::LmToFMod(forwardVec), LMVector3::LmToFMod(upwardVec));
#endif // _DEBUG

	*_lastPos = gameObject->GetTransform().position;
}

void LocoMotor::AudioListener::Start() {
	*_lastPos = gameObject->GetTransform().position;
}