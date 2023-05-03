#pragma once
#ifndef _PARTICLEHELPER_H_
#define _PARTICLEHELPER_H_

#include <unordered_map>
#include <string>
#include <Ogre.h>
#include "RenderEntity.h"

namespace OgreWrapper {
	class ParticleHelper : public RenderEntity {

	public:
		ParticleHelper(Ogre::ParticleSystem* sys);
		~ParticleHelper();

		void AddEmitter(std::string name, const Ogre::Vector3& position);
		void AddEmitter(const Ogre::Vector3& position);

		Ogre::ParticleEmitter* GetEmitter(std::string name);

		void RemoveEmitter(std::string name);
		void RemoveEmitter();

		void MoveEmitter(std::string name, const Ogre::Vector3& position);

		void RotateEmitter(std::string name, const Ogre::Vector3& rotation);

		void SetEmitting(bool emitting);
		void SetEmitting(std::string name, bool emitting);

		void SetEmissionDuration(std::string name, float duration);

		void SetEmissionRate(std::string name, float rate);

		void SetEmissionPower(std::string name, float power);
		void SetEmissionPower(std::string name, float minPower, float maxPower);

		Ogre::MovableObject* GetMovObj() override;


	private:
		Ogre::ParticleSystem* _particleSystem;

		std::unordered_map <std::string, Ogre::ParticleEmitter*> _emitters;


	};
}


#endif // !LM_PARTICLEHELPER

