#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

#define SET_NAME(cName)\
	constexpr static std::string name = cName;
#include <iostream>
namespace LocoMotor {
	class GameObject;
	class Component {
	public:
		static std::string name;

		virtual ~Component () = default;
		
		virtual void Start () {
		}
		virtual void Update (float dt) {
		}
		virtual void Render () {
		}
		void SetContext (GameObject* ent);
		GameObject* GetContext ();
	protected:
		Component () = default;

		GameObject* ent;
	};
}

#endif 

