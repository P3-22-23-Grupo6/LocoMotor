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

	private:
		Ogre::ParticleSystem* _particleSystem;

		std::map <std::string, Ogre::ParticleEmitter*> _emitters;
		
		
	};
}


#endif // !LM_PARTICLEHELPER

