#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

namespace LocoMotor {
	class GameObject;
	class Component {
	public:
		virtual void Start () {
		}
		virtual void Update () {
		}
		virtual void Render () {
		}
		void SetContext (GameObject* ent);
	protected:
		Component () = default;
		virtual ~Component () = default;
		GameObject* ent;
	};
}

#endif 

