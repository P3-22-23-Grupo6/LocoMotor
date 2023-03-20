#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

#include <iostream>
namespace LocoMotor {
	class GameObject;
	class Component {
	public:
		const static std::string name;

		virtual ~Component () = default;
		
		virtual void Start () {
		}
		virtual void Update (float dt) {
		}
		virtual void Render () {
		}
		void SetContext (GameObject* ent);
	protected:
		Component () = default;

		GameObject* ent;
	};
}

#endif 

