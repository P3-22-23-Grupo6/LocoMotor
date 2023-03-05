#pragma once
#ifndef LM_GAMEOBJECT
#define LM_GAMEOBJECT

#include "LMVector.h"
#include "Component.h"
#include <map>

//HITO 1 POC
#include "Renderer3D.h"
#include "BulletRigidBody.h"


namespace LocoMotor {
	struct Transform {
		LMVector3 position;
		LMVector3 rotation;
		LMVector3 scale;
		LMQuaternion direction;
	};

	class GameObject {
	public:
		GameObject ();
		virtual ~GameObject ();

		void update(float dt);
		
		//ogre renderer using ogremanager

		
		template<typename T, typename ...Ts>
		T* AddComponent (Ts&& ...params){
			if (_componentsByName.count (T::name) > 0) {
				return _componentsByName.at (T::name);
			}
			else {
				Component* comp = new T (std::forward<Ts> (params)...);
				component->SetContext (this);
				_componentsByName.insert ({ T::name, comp });
			}
			//EJ.:
			//ent->AddComponent<Camera>(10,0,0);
			
			//bool comps[Camera::id] == true -> error
		};

		template <typename T> 
		void RemoveComponent () {
			if (_componentsByName.count (T::name) == 0) {
				//Error: no component exists with that name
			}
			auto comp = _componentsByName.find(T::name);
			delete comp.second;
			_componentsByName.erase (comp);

		}

		template <typename T>
		T* GetComponent() {
			if (_componentsByName.count(T::name) == 0) {
				//Error: no component exists with that name
			}
			return _componentsByName.at (T::name);
		}

		Transform GetTransform();

		void SetPosition (LMVector3 pos);
		void SetRotation (LMVector3 rot);
		void SetScale (LMVector3 sc);
		void SetDirection (LMQuaternion dir);

		//HITO 1 POC

		void SetRigidBody(BulletWrapper::BulletRigidBody* rb);

		void SetRenderer(OgreWrapper::Renderer3D* renderer);

	private:
		Transform _tr;
		std::map<std::string, Component*> _componentsByName;

		//HITO 1 POC
		BulletWrapper::BulletRigidBody* _rigidBody;
		OgreWrapper::Renderer3D* _renderer;

	};
}


#endif