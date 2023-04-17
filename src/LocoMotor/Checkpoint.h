//#pragma once
//
////namespace LocoMotor {
////	class Component;
////}
//#include "Component.h"
//
////namespace OgreWrapper {
////	class RenderScene;
////	class Node;
////}
//
//namespace LocoMotor {
//	class GameObject;
//	class RigidBodyComponent;
//
//	class Checkpoint : public Component {
//	public:
//		const static std::string name;
//		static std::string GetName() {
//			return "CheckPoint";
//		};
//		Checkpoint();
//		//Checkpoint(GameObject* player = nullptr, int checkpointIndex = 0);
//
//		void Start(GameObject* player, int checkpointIndex);
//		void Update(float dt) override;
//
//	private:
//
//		int _checkpointIndex;
//		bool checked; // Si el jugador ya ha alcanzado este checkpoint en esta vuelta
//
//		RigidBodyComponent* _rb;
//		GameObject* _player;
//	};
//}