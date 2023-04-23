#include "ParticleHelper.h"

#include <OgreParticleSystem.h>
#include <OgreParticleEmitter.h>

#include <Ogre.h>

using namespace OgreWrapper;

ParticleHelper::ParticleHelper(Ogre::ParticleSystem* sys) {
		_particleSystem = sys;
	}

	ParticleHelper::~ParticleHelper() {
	}

	

	void ParticleHelper::AddEmitter(std::string name, const Ogre::Vector3&  position) {
		if (_emitters.find(name) == _emitters.end()) {
			_emitters.insert({ name, _particleSystem->addEmitter(name) });
			_emitters[name]->setPosition(position);
		}
		else {
			int num = 0;
			bool found = false;
			std::string newName = name + std::to_string(num);
			while (!found) {

				if (_emitters.find(newName) == _emitters.end()) {
					_emitters.insert({ newName, _particleSystem->addEmitter(newName) });
					_emitters[newName]->setPosition(position);

					found = true;
				}
				else {
					num++;
					newName = name + std::to_string(num);
				}
			}
		}
	}

	void ParticleHelper::AddEmitter(const Ogre::Vector3&  position) {
		std::string name = "unnamedEmitter";
		AddEmitter(name, position);
	}

	Ogre::ParticleEmitter* OgreWrapper::ParticleHelper::GetEmitter(std::string name) {
		if (_emitters.find(name) != _emitters.end()) {
			return _emitters[name];
		}
		else {
			size_t num = _emitters.size();
			bool found = false;
			std::string newName = name + std::to_string((unsigned long long)num);
			while (!found) {

				if (_emitters.find(newName) != _emitters.end()) {
					return _emitters[newName];
				}
				else {
					num++;
					newName = name + std::to_string((unsigned long long)num);
				}
			}
		}
		return nullptr;
	}

	void ParticleHelper::RemoveEmitter(std::string name) {
		if (_emitters.find(name) != _emitters.end()) {
			_particleSystem->removeEmitter(_emitters[name]);
			_emitters.erase(name);
		}
		else {
			size_t num = _emitters.size();
			bool found = false;
			std::string delName = name + std::to_string((unsigned long long)num);
			while (!found) {

				if (_emitters.find(delName) == _emitters.end()) {
					_particleSystem->removeEmitter(_emitters[delName]);
					_emitters.erase(delName);

					found = true;
				}
				else {
					num++;
					delName = name + std::to_string((unsigned long long)num);
				}
			}
		}
	}

	void ParticleHelper::RemoveEmitter() {
		std::string name = "unnamedEmitter";
		RemoveEmitter(name);
	}

	void OgreWrapper::ParticleHelper::MoveEmitter(std::string name, const Ogre::Vector3&  position) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setPosition(position);
	}

	void OgreWrapper::ParticleHelper::RotateEmitter(std::string name, const Ogre::Vector3&  rotation) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setDirection(rotation);
	}

	void OgreWrapper::ParticleHelper::SetEmitting(std::string name, bool emitting) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setEnabled(emitting);
	}

	void OgreWrapper::ParticleHelper::SetEmitting(bool emitting) {
		_particleSystem->setEmitting(emitting);
	}

	void OgreWrapper::ParticleHelper::SetEmissionDuration(std::string name, float duration) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setDuration(duration);
	}

	void OgreWrapper::ParticleHelper::SetEmissionRate(std::string name, float rate) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setEmissionRate(rate);
	}

	void OgreWrapper::ParticleHelper::SetEmissionPower(std::string name, float power) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setParticleVelocity(power);
	}
	
	void OgreWrapper::ParticleHelper::SetEmissionPower(std::string name, float minPower, float maxPower) {
		Ogre::ParticleEmitter* emitter = GetEmitter(name);
		emitter->setParticleVelocity(minPower, maxPower);
	}

	Ogre::MovableObject* OgreWrapper::ParticleHelper::GetMovObj() {
		return _particleSystem;
	}

