#pragma once

#ifndef LM_COMPONENT
#define LM_COMPONENT

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <string>

namespace LocoMotor {
	class GameObject;

	class MOTOR_API Component {
	public:
		/// @brief Destructor
		virtual ~Component() = default;
		/// @brief Inits the component with parameters from lua
		virtual void Init(std::vector<std::pair<std::string, std::string>>& params) {
		};
		/// @brief Initialize the component
		virtual void PreStart() {
		}
		/// @brief Initialize the component
		virtual void Start() {
		}
		/// @brief Update the component
		virtual void Update(float dt) {
		}
		/// @brief PreUpdate the component
		virtual void PreUpdate(float dt) {
		}
		/// @brief Render the component
		virtual void Render() {
		}
		/// @brief This method is called when the component is active again
		virtual void OnEnable() {
		};
		/// @brief This method is called when the component is no longer active
		virtual void OnDisable() {
		};
		/// @brief This method is automatically called the first frame the gameobject this component is attached to collides
		/// with another gameobject
		virtual void OnCollisionEnter(GameObject* other) {
		};
		/// @brief This method is automatically called every frame the gameobject this component is attached to collides
		/// with another gameobject
		virtual void OnCollisionStay(GameObject* other) {
		};
		/// @brief This method is automatically called the first frame the gameobject this component is attached to no longer 
		/// collides with another gameobject
		virtual void OnCollisionExit(GameObject* other) {
		};

		/// @brief Returns the gameobject this component is attached to
		GameObject* GetContext();
		/// @brief Set the component to a gameobject
		void SetContext(GameObject* ent);
		/// @brief Sets whether the component is active or not
		void SetActive(bool active);
		/// @brief Returns true if the component is active
		bool isEnabled();
		/// @brief Inits the component
		virtual void InitComponent() {
		};
		GameObject* gameObject;
	protected:
		bool _enabled;
		/// @brief Constructor
		Component();

	};
}

#endif 

