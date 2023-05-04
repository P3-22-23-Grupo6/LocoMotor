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

		/// @brief Adds an emmiter with a name in a position
		void AddEmitter(std::string name, const Ogre::Vector3& position);
		/// @brief Adds an emmiter without a name in a position
		void AddEmitter(const Ogre::Vector3& position);
		/// @brief Gets an emmiter with a name
		Ogre::ParticleEmitter* GetEmitter(std::string name);
		/// @brief Removes an emmiter with a name
		void RemoveEmitter(std::string name);
		/// @brief Removes the unnamed emmiter
		void RemoveEmitter();
		/// @brief Moves an emmiter with a name to a position
		void MoveEmitter(std::string name, const Ogre::Vector3& position);
		/// @brief Rotates an emmiter with a name to a rotation
		void RotateEmitter(std::string name, const Ogre::Vector3& rotation);
		/// @brief Sets the particle system emmiting boolean
		void SetEmitting(bool emitting);
		/// @brief Sets the emitter with a name, emmiting boolean
		void SetEmitting(std::string name, bool emitting);
		/// @brief Sets the emitter with a name, the emmision duration
		void SetEmissionDuration(std::string name, float duration);
		/// @brief Sets the emitter with a name, the emmision rate
		void SetEmissionRate(std::string name, float rate);
		/// @brief Sets the emitter with a name, the emmision power
		void SetEmissionPower(std::string name, float power);
		/// @brief Sets the emitter with a name, the emmision power between minimun power and maximun power
		void SetEmissionPower(std::string name, float minPower, float maxPower);

		Ogre::MovableObject* GetMovObj() override;


	private:
		Ogre::ParticleSystem* _particleSystem;

		std::unordered_map <std::string, Ogre::ParticleEmitter*> _emitters;

	};
}


#endif // !LM_PARTICLEHELPER

