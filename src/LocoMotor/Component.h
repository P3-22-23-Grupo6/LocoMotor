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
		GameObject* GetContext ();
		/// @brief Set the component to a gameobject
		void SetContext(GameObject* ent);

		virtual void InitComponent();

	protected:
		/// @brief Constructor
		Component() = default;

		GameObject* gameObject;
	};
}

#endif 

