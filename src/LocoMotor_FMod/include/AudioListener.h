#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

#include <list>

struct FMOD_VECTOR;
namespace FmodWrapper {
	class AudioManager;
}
namespace FMOD {
	class System;
}

namespace FmodWrapper {

	class AudioListener {

	public:
		AudioListener();
		~AudioListener();

		/// @brief Set the world attributes of the listener
		/// @param newPos The new position of the listener (pass NULL or 0 to not update position)
		/// @param newVel The new velocity of the listener (pass NULL or 0 to not update velocity)
		/// @param forward The direction the listener is facing MUST BE NORMALIZED (pass NULL or 0 to not update)
		/// @param up The new upwards direction of the listener MUST ALSO BE NORMALIZED (pass NULL or 0 to not update)
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short SetTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up);

		unsigned short ChangeIndex(int index);

		int GetIndex();

		std::list<AudioListener*>::iterator GetIterator();

	private:

		int _fIndex;

		FmodWrapper::AudioManager* _man;

		std::list<AudioListener*>::iterator _thisIT;
	};
}

#endif