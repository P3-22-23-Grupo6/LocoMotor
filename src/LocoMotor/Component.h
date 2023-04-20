#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

#include <iostream>
#include <vector>
#include <string>

namespace LocoMotor {
	class GameObject;
	 class Component {
	public:
		/// @brief Destructor
		virtual ~Component() = default;

		virtual void Init(std::vector<std::pair<std::string, std::string>>& params) {};
		/// @brief Initialize the component
		virtual void Start() {
		}
		/// @brief Update the component
		virtual void Update(float dt) {
		}
		/// @brief Render the component
		virtual void Render() {
		}
		virtual void OnEnable() {
		};
		virtual void OnDisable() {
		};
		virtual void OnCollisionEnter(GameObject* other) {
		};
		virtual void OnCollisionStay(GameObject* other) {
		};
		virtual void OnCollisionExit(GameObject* other) {
		};

		GameObject* GetContext ();
		/// @brief Set the component to a gameobject
		void SetContext(GameObject* ent);
		void SetActive(bool active);
		bool isEnabled();
		MOTOR_API virtual void InitComponent(){ };
		
		//GameObject* GetGameobject();

		GameObject* gameObject;
	protected:
		bool enabled=true;
		/// @brief Constructor
		Component() = default;

	};
}

#endif 

