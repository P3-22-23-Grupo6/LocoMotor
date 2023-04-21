#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "Component.h"

namespace OgreWrapper {
	class Renderer3D;
	
	class Node;
	class RenderScene;
}

namespace LocoMotor {
	class GameObject;
	class MOTOR_API MeshRenderer: public Component {
	public:
		const static std::string name;
		static std::string GetName() {
			return "MeshRenderer";
		};
		MeshRenderer();
		~MeshRenderer();

		void Render();

		void Start() override;
		void Start(std::string name, std::string file, std::string mat);
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitComponent() override;
		//OgreWrapper::Node* GetNode();
		OgreWrapper::Renderer3D* GetRenderer();

	private:

		OgreWrapper::Renderer3D* _rend3D=nullptr;
		//OgreWrapper::RedererEntity* _rendEnt;

		GameObject* _gobj;
		//OgreWrapper::Renderer3D* _msh=nullptr;

		std::string _name;
		std::string _src;
		std::string _mat;

		OgreWrapper::RenderScene* _rndScn;
		OgreWrapper::Node* _nod;
		
		//OgreWrapper::Node* _node;

	};
}