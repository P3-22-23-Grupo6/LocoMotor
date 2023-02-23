#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

typedef struct FMOD_VECTOR;
class AudioManager;
namespace FMOD {
	class System;
}

class AudioListener {

public:
	AudioListener (AudioManager* manager/*gameobject, etc*/);
	~AudioListener ();

	/// @brief Actualizara los datos del listener dependiendo del gameobject asociado
	/// @param deltaTime En este caso, se utiliza para calcular la velocidad del gameobject
	void Update (const float& deltaTime);

	/// @brief Lo unico que hace es rotar deltaTime radianes el listener de fmod asociado
	/// @param deltaTime Bruh
	void UpdateFunni (const float& deltaTime);

private:

	// + lo tipico de gameobject y tal

	int _fIndex;

	float _elapsedTime;

	AudioManager* man;

	FMOD_VECTOR* _posRemember;
};


#endif