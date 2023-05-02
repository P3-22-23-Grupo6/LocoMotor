#pragma once
#ifndef LM_GAMEOBJECT
#define LM_GAMEOBJECT
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "LMVector.h"
#include "Component.h"
#include "ComponentsFactory.h"
#include <map>
#include <unordered_map>

//HITO 1 POC



namespace OgreWrapper {
	class Node;
	class Renderer3D;
}


namespace LocoMotor {

	class Scene;
	class Transform;

    class MOTOR_API GameObject {
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
		template<typename ...Ts>
		inline Component* AddComponent(std::string name ,Ts&& ...params) {
			if (_componentsByName.count(name) > 0) {
				return nullptr;
			}
			else {
				Component* comp = ComponentsFactory::GetInstance()->CreateComponent(name);
				comp->SetContext(this);
				comp->InitComponent();
				_componentsByName.insert({ name, comp });

				return comp;
			}
			//EJ.:
			//ent->AddComponent<Camera>(10,0,0);

			//bool comps[Camera::id] == true -> error
		};

		void AddComponent(std::string name, std::vector<std::pair<std::string, std::string>>& params);

		/// @brief Remove a Component
		/// @param T The type of the component to remove
		void RemoveComponent(std::string name) {
			if (_componentsByName.count(name) == 0) {
				//Error: no component exists with that name
			}
			auto comp = _componentsByName.find(name);
			delete comp->second;
			_componentsByName.erase(comp);

		}

		/// @brief Get a Component
		/// @param T The type of the component to get
		template <typename T>
		inline T* GetComponent() {
			auto it = _componentsByName.begin();
			T* comp = nullptr;
			while (it != _componentsByName.end() && comp == nullptr) {
				comp = dynamic_cast<T*>(it->second);
				it++;
			}
			return comp;
			//if (_componentsByName.count(name) == 0) {
			//	//Error: no component exists with that name
			//	return nullptr;
			//}
			//return static_cast<T*>(_componentsByName.at(name));
		}
		/// @brief This method is automatically called the first frame this gameobject collides
		/// with another gameobject
		void OnCollisionEnter(GameObject* other);
		/// @brief This method is automatically called every frame this gameobject collides
		/// with another gameobject
		void OnCollisionStay(GameObject* other);
		/// @brief This method is automatically called the first frame this gameobject no longer 
		/// collides with another gameobject
		void OnCollisionExit(GameObject* other);

		/// @brief Set the position of the GameObject
		void SetPosition(LMVector3 pos);
		/// @brief Set the rotation of the GameObject
		void SetRotation(LMQuaternion rot);
		/// @brief Set the scale of the GameObject
		void SetScale(LMVector3 sc);
		/// @brief Returns the transform component of this gameobject
		Transform* GetTransform();

		std::string GetName();

		//HITO 1 POC

		/// @brief Set the rigid body of the GameObject+
		/// @param rb The rigid body to set
		//void SetRigidBody(PhysicsWrapper::BulletRigidBody* rb);

		/// @brief Set the renderer of the GameObject
		/// @param renderer The renderer to set
		void SetRenderer(OgreWrapper::Node* node);
		/// @brief Sets the scene where the gameobject is
		void SetContext(Scene* scn);
		/// @brief Returns the scene where the gameobject is
		Scene* GetScene();
		/// @brief Starts every component of this gameobject
		void StartComp();
		/// @brief Sets the transform component of this gameobject
		/// @param newTrans 
		void RegisterTransform(Transform* newTrans);
		//Pruebaval
		inline void setMovable(bool b) {
			movable = b;
		}

		bool physicsBasedMovement;
	private:
		std::unordered_map<std::string, Component*> _componentsByName;
		Scene* scene;


		Transform* transform;

		//HITO 1 POC
		//PhysicsWrapper::BulletRigidBody* _rigidBody;
		OgreWrapper::Renderer3D* _renderer;
		OgreWrapper::Node* _node;

		//Prueba
		bool movable=false;
		double tiltAmount;

		LMVector3 localVelocity = LMVector3(0, 0, 0);
		bool _destructed = false;
	};
}


#endif