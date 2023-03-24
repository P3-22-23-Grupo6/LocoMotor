#pragma once
#ifndef _PARTICLEHELPER_H_
#define _PARTICLEHELPER_H_

#include "lmVector.h"


namespace OgreWrapper{
	class ParticleHelper {
		
	public:
		ParticleHelper(Ogre::ParticleSystem* sys);
		~ParticleHelper();

		void AddEmitter(std::string name, LMVector3 position);
		void AddEmitter(LMVector3 position);

		Ogre::ParticleEmitter* GetEmitter(std::string name);

		void RemoveEmitter(std::string name);
		void RemoveEmitter();

		void MoveEmitter(std::string name, LMVector3 position);

		void RotateEmitter(std::string name, LMVector3 rotation);
		
		void SetEmitting(bool emitting);
		void SetEmitting(std::string name, bool emitting);

		void SetEmissionDuration(std::string name, float duration);
		
		void SetEmissionRate(std::string name, float rate);

		void SetEmissionPower(std::string name, float power);
		void SetEmissionPower(std::string name, float minPower, float maxPower);
		

	private:
		Ogre::ParticleSystem* _particleSystem;

		std::map <std::string, Ogre::ParticleEmitter*> _emitters;
		
		
	};
}


#endif // !LM_PARTICLEHELPER

