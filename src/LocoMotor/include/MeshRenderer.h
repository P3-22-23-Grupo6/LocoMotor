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
	class LMVector3;
	class GameObject;
	class MOTOR_API MeshRenderer : public Component {
	public:
		MeshRenderer();
		~MeshRenderer();

		void Render();
		void ChangeTexOffset(std::string matName, float newX, float newY);
		void CreateBillboard(LMVector3 billPos, std::string matName);
		/// @brief Initializes and attaches a renderer to a node in an Ogre scene.
		void PreStart() override;

		void Start(std::string name, std::string file, std::string mat, bool isStatic = false);

		/// @brief Initializes the parameters of a MeshRenderer object using a vector of pairs.
		/// @param params A vector of pairs, where each pair contains a string key and a string value. These
		/// pairs represent the parameters that are passed to the Init() function of the MeshRenderer class. The
		/// function loops through each pair and checks the key to determine which member variable of the
		/// MeshRenderer class to set with the
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;
		void InitRuntime(std::string meshSource, std::string materialName = "");

		void InitComponent() override;

		/// @brief Returns a pointer to a 3D renderer object from a mesh renderer object.
		/// @return An object of type OgreWrapper::Renderer3D* is being returned.
		OgreWrapper::Renderer3D* GetRenderer();

		void ChangeMaterial(std::string newMaterial);
		/// @brief Sets the Mesh renderer visible/invisible
		void SetVisible(bool value);
	private:

		OgreWrapper::Renderer3D* _rend3D = nullptr;

		GameObject* _gobj;

		std::string _name;
		std::string _src;
		std::string _mat;

		OgreWrapper::RenderScene* _rndScn;
		OgreWrapper::Node* _node;
		bool _isStatic;
	};
}