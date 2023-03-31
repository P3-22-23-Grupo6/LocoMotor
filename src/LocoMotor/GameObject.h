#pragma once
#ifndef LM_GAMEOBJECT
#define LM_GAMEOBJECT

#include "LocoMotor_Utils/lmVector.h"
#include "Component.h"
#include <map>

//HITO 1 POC
#include "Renderer3D.h"
#include "BulletRigidBody.h"

namespace OgreWrapper {
	class Node;
}


namespace LocoMotor {
	struct Transform {
		LMVector3 position;
		LMVector3 rotation;
		LMVector3 scale;
		LMQuaternion direction;
	};

	class Scene;

	class GameObject {
	public:
		/// @brief Constructor
		GameObject(OgreWrapper::Node* node);
		/// @brief Destructor
		virtual ~GameObject();

		/// @brief Update the GameObject and all its components
		void Update(float dt);

		//ogre renderer using ogremanager

		/// @brief Add a component to the GameObject
		/// @param T The type of the component to add
		template<typename T, typename ...Ts>
		void AddComponent(Ts&& ...params) {
			if (_componentsByName.count(T::name) > 0) {
				return;
			}
			else {
				Component* comp = new T(std::forward<Ts>(params)...);
				comp->SetContext(this);
				comp->InitComponent();
				_componentsByName.insert({ T::name, comp });
			}
			//EJ.:
			//ent->AddComponent<Camera>(10,0,0);

			//bool comps[Camera::id] == true -> error
		};



		/// @brief Remove a Component
		/// @param T The type of the component to remove
		template <typename T>
		void RemoveComponent() {
			if (_componentsByName.count(T::name) == 0) {
				//Error: no component exists with that name
			}
			auto comp = _componentsByName.find(T::name);
			delete comp.second;
			_componentsByName.erase(comp);

		}

		/// @brief Get a Component
		/// @param T The type of the component to get
		template <typename T>
		T* GetComponent() {
			if (_componentsByName.count(T::name) == 0) {
				//Error: no component exists with that name
				return nullptr;
			}
			return static_cast<T*>(_componentsByName.at(T::name));
		}

		/// @brief Get the transform of the GameObject
		Transform GetTransform();

		/// @brief Set the position of the GameObject
		void SetPosition(LMVector3 pos);
		/// @brief Set the rotation of the GameObject
		void SetRotation(LMVector3 rot);
		/// @brief Set the scale of the GameObject
		void SetScale(LMVector3 sc);
		/// @brief Set the transform direction of the GameObject
		void SetDirection(LMQuaternion dir);

		//HITO 1 POC

		/// @brief Set the rigid body of the GameObject+
		/// @param rb The rigid body to set
		//void SetRigidBody(PhysicsWrapper::BulletRigidBody* rb);

		/// @brief Set the renderer of the GameObject
		/// @param renderer The renderer to set
		void SetRenderer(OgreWrapper::Node* node);

		void SetContext(Scene* scn);

		Scene* GetScene();

		OgreWrapper::Node* GetNode();

		void StartComp();

		//Prueba
		void setMovable(bool b) {
			movable = b;
		}

	private:
		Transform _tr;
		std::map<std::string, Component*> _componentsByName;
		Scene* scene;

		//HITO 1 POC
		//PhysicsWrapper::BulletRigidBody* _rigidBody;
		OgreWrapper::Renderer3D* _renderer;
		OgreWrapper::Node* _node;

		//Prueba
		bool movable=false;
	};
}


#endif