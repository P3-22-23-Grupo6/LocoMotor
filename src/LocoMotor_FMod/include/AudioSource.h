#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE
#include <list>
#include <lmVector.h>

typedef struct FMOD_VECTOR;
namespace FMOD {
	class Channel;
}
namespace FmodWrapper {
	class AudioManager;
}

class AudioSource {

	FmodWrapper::AudioManager* _man;

	FMOD_VECTOR* _posRemember;

	std::list<FMOD::Channel*> _chList;

	AudioSource ();
	~AudioSource ();

	uint16_t AddSound (const uint32_t id, const char* fileName);

	uint16_t PlaySound (const uint32_t id);

	void SetPosition (const LMVector3& newPos, bool updateVelocity = true);
	void SetVelocity (const LMVector3& newVel);


};

#endif // !AUDIOSOURCE


