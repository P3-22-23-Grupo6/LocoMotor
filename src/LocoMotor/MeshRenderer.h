#pragma once
#include <string>
#include "Component.h"
#include "GameObject.h"

namespace OgreWrapper {
	class Renderer3D;
	
	class Node;
	class RenderScene;
}

namespace LocoMotor {
	class GameObject;
	class MeshRenderer: public Component {
	public:
		const static std::string name;

		MeshRenderer(std::string name,std::string file,std::string mat,OgreWrapper::RenderScene* rndSc);
		~MeshRenderer();

		void Render();

		void Start() override;

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