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
		/// @brief Initializes and attaches a renderer to a node in an Ogre scene.
		void PreStart() override;

		void Start(std::string name, std::string file, std::string mat, bool isStatic = false);

		/// @brief Initializes the parameters of a MeshRenderer object using a vector of pairs.
		/// @param params A vector of pairs, where each pair contains a string key and a string value. These
		/// pairs represent the parameters that are passed to the Init() function of the MeshRenderer class. The
		/// function loops through each pair and checks the key to determine which member variable of the
		/// MeshRenderer class to set with the
		void Init(std::vector<std::pair<std::string, std::string>>& params) override;

		void InitComponent() override;

		/// @brief Returns a pointer to a 3D renderer object from a mesh renderer object.
		/// @return An object of type OgreWrapper::Renderer3D* is being returned.
		OgreWrapper::Renderer3D* GetRenderer();

		/// @brief Rotates a mesh renderer object using a given set of new rotation values.
		/// @param newRotation newRotation is a LMVector3 object that represents the new rotation to be applied
		/// to the MeshRenderer. It contains three float values representing the rotation around the x, y, and z
		/// axes respectively.
		void Rotate(LMVector3 newRotation);

	private:

		OgreWrapper::Renderer3D* _rend3D = nullptr;

		GameObject* _gobj;

		std::string _name;
		std::string _src;
		std::string _mat;

		OgreWrapper::RenderScene* _rndScn;
		OgreWrapper::Node* _nod;
		bool _isStatic;



	};
}