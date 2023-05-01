#include "AudioListener.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMVector.h"
#include "LocoMotor_FMod/include/AudioListener.h"
#include "LocoMotor_FMod/include/AudioManager.h"
#include "LmVectorConverter.h"
#include "LogSystem.h"

using namespace LocoMotor;


/**
 * This is the constructor for the AudioListener class, which initializes its member variables.
 */
AudioListener::AudioListener() {
	_list = nullptr;
	_lastPos = LMVector3();
	_lastVel = LMVector3();
}
/**
 * This is a destructor for the AudioListener class that deletes a pointer to a list.
 */
AudioListener::~AudioListener() {
	delete _list;
}

/**
 * The function initializes the last position of an audio listener object.
 */
void LocoMotor::AudioListener::Start() {
	_lastPos = gameObject->GetTransform()->GetPosition();
}

/**
 * The function initializes a new instance of the FmodWrapper::AudioListener class.
 */
void LocoMotor::AudioListener::InitComponent() {
	_list = new FmodWrapper::AudioListener();
}

/**
 * The function updates the position and velocity of an audio listener object in the game engine.
 * @brief This function updates the position and velocity of an audio listener object in the game engine.
 * @param dt dt stands for delta time, which is the time elapsed between two consecutive frames in the
 * game. It is used to calculate the velocity of the game object.
 */
void LocoMotor::AudioListener::Update(float dt) {

	LMVector3 forwardVec = gameObject->GetTransform()->GetRotation().Forward() * -1;
	LMVector3 upwardVec = gameObject->GetTransform()->GetRotation().Up();

	LMVector3 vel = _lastVel + ((((gameObject->GetTransform()->GetPosition() - _lastPos) / (dt / 1000.f)) - _lastVel) * 0.8f);

#ifdef _DEBUG
	unsigned short err = _list->SetTransform(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(vel), LmToFMod(forwardVec), LmToFMod(upwardVec));
	if (err > 0) {
		std::cout << "AudioListener::Update(): " << FmodWrapper::AudioManager::GetInstance()->GetError(err) << std::endl;
	}
#else
	unsigned short err = _list->SetTransform(LmToFMod(gameObject->GetTransform()->GetPosition()), LmToFMod(vel), LmToFMod(forwardVec), LmToFMod(upwardVec));
#endif // _DEBUG

	if (err > 0) {
		LogSystem::GetInstance()->Save(0, "AudioListener::Update(): " + (std::string)FmodWrapper::AudioManager::GetInstance()->GetError(err));
	}

	_lastPos = gameObject->GetTransform()->GetPosition();
	_lastVel = vel;
}


