#pragma once
#ifndef LM_COMPONENT
#define LM_COMPONENT

#define SET_NAME(cName)\
	constexpr static std::string name = cName;

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
	protected:
		Component () = default;

		GameObject* ent;
	};
}

#endif 

