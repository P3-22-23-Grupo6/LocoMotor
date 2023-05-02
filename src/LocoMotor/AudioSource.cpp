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
}

/**
 * This is a destructor for the AudioSource class that deletes the _src object.
 */
AudioSource::~AudioSource() {
	delete _src;
}

/**
 * The function initializes a new audio source component using the FmodWrapper library in C++.
 */
void LocoMotor::AudioSource::InitComponent() {
	_src = new FmodWrapper::AudioSource();
}

/**
 * The function initializes an audio source with various parameters passed in as a vector of pairs.
 * @brief Initialize an audio source with various parameters passed in as a vector of pairs.
 * @param params A vector of pairs, where each pair contains a string representing a parameter name and
 * a string representing the parameter value.
 */
void LocoMotor::AudioSource::Init(std::vector<std::pair<std::string, std::string>>& params) {
	_src = new FmodWrapper::AudioSource();
	int loops = 0;
	unsigned int loopStart = 0;
	unsigned int loopEnd = 0xffffffff;
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "vol" || params[i].first == "volume") {
			SetVolume(std::stof(params[i].second));
		}
		else if (params[i].first == "freq" || params[i].first == "frequency") {
			SetFreq(std::stof(params[i].second));
		}
		else if (params[i].first == "preloadaudio" || params[i].first == "loadaudio" || params[i].first == "load") {
			_src->AddSound(params[i].second.c_str());
		}
		else if (params[i].first == "loops") {
			loops = std::stoi(params[i].second);
		}
		else if (params[i].first == "loopStart") {
			int a = std::stoi(params[i].second);
			if (a < 0)
				a = 0;
			loopStart = a;
		}
		else if (params[i].first == "loopEnd") {
			int a = std::stoi(params[i].second);
			if (a < 0)
				a = 0;
			loopEnd = a;
		}
		else if (params[i].first == "playonStart") {
			Play(params[i].second.c_str(), loops, loopStart, loopEnd);
		}
	}
}

/**
 * The function updates the position and velocity of an audio source using the position of the game
 * object it is attached to.
 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
 * usually measured in seconds. In this code snippet, it is used to calculate the position and velocity
 * of the audio source based on the object's current position and the time elapsed since the last
 * update.
 */
void LocoMotor::AudioSource::Update(float dt) {
#ifdef _DEBUG
	if (_lastError != 0) {
		std::cout << FmodWrapper::AudioManager::GetInstance()->GetError(_lastError) << std::endl;
		_lastError == 0;
	}
#endif // _DEBUG
	_src->SetPositionAndVelocity(LmToFMod(gameObject->GetTransform()->GetPosition()), dt / 1000.f);
}

/**
 * The function plays an audio file with specified looping parameters.
 * @brief Plays an audio file with specified looping parameters.
 * @param fileName The name or path of the audio file to be played.
 * @param loop The "loop" parameter is an integer that determines how many times the audio file should
 * be played in a loop. If the value is 0, the audio file will play once. If the value is 1, the audio
 * file will play twice (once and then again in a loop). If
 * @param loopStart loopStart is an optional parameter that specifies the starting point of the loop in
 * milliseconds. If loopStart is not specified, the loop will start from the beginning of the audio
 * file.
 * @param loopEnd The loopEnd parameter is an unsigned integer that represents the end point of a loop
 * in the audio file being played. This parameter is used in conjunction with the loopStart parameter
 * to specify a loop range within the audio file. If loopEnd is set to 0, the entire audio file will be
 * played
 */
void LocoMotor::AudioSource::Play(const char* fileName, const int loop, const unsigned int loopStart, const unsigned int loopEnd) {
	_lastError = _src->PlaySound(fileName, loop, loopStart, loopEnd);
}

/**
 * The function plays a sound effect at a specified position and volume using a given file name.
 * @brief Plays a sound effect at a specified position and volume using a given file name.
 * @param fileName A string representing the name or path of the audio file to be played.
 * @param position The position parameter is of type LMVector3, which is likely a 3D vector
 * representing a position in space. It is used to specify the location in 3D space where the audio
 * should be played from.
 * @param volume The volume parameter is a float value that represents the loudness of the audio clip
 * to be played. It ranges from 0.0f (silent) to 1.0f (maximum volume).
 */
void LocoMotor::AudioSource::PlayOneShot(const char* fileName, const LMVector3& position, const float volume) {
	_lastError = _src->PlayOneShot(fileName, LmToFMod(position), volume);
}

/**
 * This function plays a sound effect at a specified position with a specified volume and pitch.
 * @brief Plays a sound effect at a specified position with a specified volume and pitch.
 * @param fileName A string representing the name or path of the audio file to be played.
 * @param position The position parameter is of type LMVector3, which is likely a 3D vector
 * representing the position of the audio source in space. This parameter is used to spatialize the
 * audio, meaning that the volume and other properties of the sound will vary depending on the
 * listener's position relative to the audio
 * @param volume The volume parameter is a float value that represents the loudness of the audio clip
 * being played. It can range from 0.0 (silent) to 1.0 (maximum volume).
 * @param pitch Pitch refers to the perceived highness or lowness of a sound. It is measured in Hertz
 * (Hz) and determines the frequency of the sound wave. In this context, the pitch parameter is used to
 * adjust the pitch of the audio clip being played by the AudioSource. A higher pitch value
 */
void LocoMotor::AudioSource::PlayOneShot(const char* fileName, const LMVector3& position, const float volume, const float pitch) {
	_lastError = _src->PlayOneShot(fileName, LmToFMod(position), volume, pitch);
}

/**
 * This function pauses or resumes a sound file in an audio source object.
 * @brief Pause or resume a sound file in an audio source object.
 * @param fileName The name of the audio file that needs to be paused or resumed.
 * @param pause A boolean value indicating whether to pause or resume the sound. If it is set to true,
 * the sound will be paused, and if it is set to false, the sound will be resumed.
 */
void LocoMotor::AudioSource::PauseSound(const char* fileName, bool pause) {
	_lastError = _src->PauseS(fileName, pause);
}

/**
 * This function pauses or resumes all sounds in an audio source object.
 * @brief Pause or resume all sounds in an audio source object.
 * @param pause A boolean value indicating whether to pause or resume the sound. If it is set to true,
 * the sound will be paused, and if it is set to false, the sound will be resumed.
 */
void LocoMotor::AudioSource::Pause(bool pause) {
	_lastError = _src->PauseSource(pause);
}

/**
 * This function stops a sound file in an audio source object.
 * @brief Stops a sound file in an audio source object.
 * @param fileName The name of the audio file that needs to be stopped.
 */
void LocoMotor::AudioSource::Stop(const char* fileName) {
	_lastError = _src->StopSound(fileName);
}

/**
 * This function stops all sounds in an audio source object.
 * @brief Stops all sounds in an audio source object.
 */
void LocoMotor::AudioSource::Stop() {
	_lastError = _src->StopSource();
}

/**
 * This function sets the volume of a sound file in an audio source object.
 * @brief Sets the volume of a sound file in an audio source object.
 * @param fileName The name of the audio file whose volume needs to be set.
 * @param volume The volume parameter is a float value that represents the loudness of the audio clip
 * being played. It can range from 0.0 (silent) to 1.0 (maximum volume).
 */
void LocoMotor::AudioSource::SetVolume(const char* fileName, const float volume) {
	_lastError = _src->SetSoundVolume(fileName, volume);
}

/**
 * This function sets the volume of all sounds in an audio source object.
 * @brief Sets the volume of all sounds in an audio source object.
 * @param volume The volume parameter is a float value that represents the loudness of the audio clip
 * being played. It can range from 0.0 (silent) to 1.0 (maximum volume).
 */
void LocoMotor::AudioSource::SetVolume(const float volume) {
	_lastError = _src->SetSourceVolume(volume);
}

/**
 * This function sets the pitch of a sound file in an audio source object.
 * @brief Sets the pitch of a sound file in an audio source object.
 * @param fileName The name of the audio file whose pitch needs to be set.
 * @param freqMult Pitch refers to the perceived highness or lowness of a sound. It is measured in Hertz
 * (Hz) and determines the frequency of the sound wave. In this context, the pitch parameter is used to
 * adjust the pitch of the audio clip being played by the AudioSource. A higher pitch value
 */
void LocoMotor::AudioSource::SetFreq(const char* fileName, const float freqMult) {
	_lastError = _src->SetSoundFreq(fileName, freqMult);
}

/**
 * This function sets the pitch of all sounds in an audio source object.
 * @brief Sets the pitch of all sounds in an audio source object.
 * @param freqMult Pitch refers to the perceived highness or lowness of a sound. It is measured in Hertz
 * (Hz) and determines the frequency of the sound wave. In this context, the pitch parameter is used to
 * adjust the pitch of the audio clip being played by the AudioSource. A higher pitch value
 */
void LocoMotor::AudioSource::SetFreq(const float freqMult) {
	_lastError = _src->SetFrequency(freqMult);
}


/**
 * The function sets the audio source mode to 3D.
 * @brief Sets the audio source mode to 3D.
 */
void LocoMotor::AudioSource::Set3D() {
	_src->SetMode3D();
}

/**
 * This function sets the audio source mode to 2D.
 * @brief Sets the audio source mode to 2D.
 */
void LocoMotor::AudioSource::Set2D() {
	_src->SetMode2D();
}
