#pragma once
#ifndef LM_GAMEOBJECT
#define LM_GAMEOBJECT

#include "LMVector.h"
#include "Component.h"
#include <map>
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

		Transform GetTransform () {
			return _tr;
		}

		void SetPosition (LMVector3 pos);
		void SetRotation (LMVector3 rot);
		void SetScale (LMVector3 sc);
		void SetDirection (LMQuaternion dir);

	private:
		Transform _tr;
		//std::vector<Component*> _components;
		std::map<std::string, Component*> _componentsByName;
	};
}


#endif