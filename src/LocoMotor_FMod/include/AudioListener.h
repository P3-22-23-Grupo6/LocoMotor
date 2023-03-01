#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

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
		AudioListener ();
		~AudioListener ();

		/// @brief Actualizara los datos del listener dependiendo del gameobject asociado
		/// @param deltaTime En este caso, se utiliza para calcular la velocidad del gameobject
		void Update (const float& deltaTime);

		/// @brief Lo unico que hace es rotar deltaTime radianes el listener de fmod asociado
		/// @param deltaTime Bruh
		void UpdateFunni (const float& deltaTime);

		///// @brief Actualizara los datos del listener dependiendo del gameobject asociado
		///// @param deltaTime En este caso, se utiliza para calcular la velocidad del gameobject
		//void Update (const uint32_t& deltaTime);

		///// @brief Lo unico que hace es rotar (deltaTime / 1000) radianes el listener de fmod asociado
		///// @param deltaTime Bruh
		//void UpdateFunni (const uint32_t& deltaTime);

	private:

		// + lo tipico de gameobject y tal

		int _fIndex;

		float _elapsedTime;

		FmodWrapper::AudioManager* man;

		FMOD_VECTOR* _posRemember;
	};
}

#endif