#include "AudioListener.h"
#include "GameObject.h"
#include "LocoMotor_Utils/lmVector.h"
#include "LocoMotor_FMod/include/AudioListener.h"
#include "LocoMotor_FMod/include/AudioManager.h"

using namespace LocoMotor;

AudioListener::AudioListener() {
	_list = new FmodWrapper::AudioListener();
	_lastPos = new LMVector3();
}

AudioListener::~AudioListener() {
	delete _list;
	delete _lastPos;
}

void LocoMotor::AudioListener::Update(float dt) {
	// TODO: ver como calcular el upward a partir del transform
	double degToRad = 0.0174533;

	LMVector3 rot = ent->GetTransform().rotation * degToRad;
	LMVector3 forwardVec = LMVector3(std::sin(rot.GetY()) * std::cos(rot.GetX()),
									 std::sin(-rot.GetX()),
									 std::cos(rot.GetX()) * std::cos(rot.GetY()));

	//No se si este esta bien calculado pero bueno xd
	LMVector3 upwardVec = LMVector3(std::sin(-rot.GetZ()),
									std::cos(rot.GetX()) * std::cos(rot.GetZ()),
									std::sin(rot.GetZ()) * std::cos(rot.GetX()));

	LMVector3 vel = (ent->GetTransform().position - *_lastPos) / dt;

#ifdef _DEBUG
	std::cout << "AudioListener::Update(): " << FmodWrapper::AudioManager::GetInstance()->GetError(_list->SetTransform(LMVector3::LmToFMod(ent->GetTransform().position), LMVector3::LmToFMod(vel), LMVector3::LmToFMod(forwardVec), LMVector3::LmToFMod(upwardVec))) << std::endl;
#else
	_list->SetTransform(LMVector3::LmToFMod(ent->GetTransform().position), LMVector3::LmToFMod(vel), LMVector3::LmToFMod(forwardVec), LMVector3::LmToFMod(upwardVec));
#endif // _DEBUG

	*_lastPos = ent->GetTransform().position;
}

void LocoMotor::AudioListener::Start() {
	*_lastPos = ent->GetTransform().position;
}
