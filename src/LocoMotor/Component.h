#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

#include <iostream>

namespace LocoMotor {
	class GameObject;
	class Component {
	public:

		/// @brief Destructor
		virtual ~Component() = default;
		/// @brief Initialize the component
		virtual void Start() {
		}
		/// @brief Update the component
		virtual void Update(float dt) {
		}
		/// @brief Render the component
		virtual void Render() {
		}
		/// @brief Set the component to a gameobject
		void SetContext(GameObject* ent);
	protected:
		/// @brief Constructor
		Component() = default;

		GameObject* gameObject;
	};
}

#endif 

