#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

typedef struct FMOD_VECTOR;
class AudioManager;
namespace FMOD {
	class System;
}

class AudioListener {

	// + lo tipico de gameobject y tal

	int _fIndex;

	AudioManager* man;

	FMOD_VECTOR* _posRemember;

public:
	AudioListener (AudioManager* manager/*gameobject, etc*/);
	~AudioListener ();

	void update (const float& deltaTime);
	void updateFunni (const float& deltaTime);
};


#endif