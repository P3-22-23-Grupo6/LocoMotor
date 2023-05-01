#include "MeshRenderer.h"
#include "Renderer3D.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Scene.h"
#include "GameObject.h"
#include "LMVector.h"
#include "Transform.h"
using namespace LocoMotor;

/**
 * This is a constructor for the MeshRenderer class that initializes its member variables.
 */
LocoMotor::MeshRenderer::MeshRenderer()
{
	_gobj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_rndScn = nullptr;
	_nod = nullptr;
	_rend3D = nullptr;
	_isStatic = false;
}


/**
 * The function initializes and attaches a renderer to a node in an Ogre scene.
 */
void MeshRenderer::Start() {
	_rndScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	_nod = _rndScn->GetNode(_name);
	const auto& aux = gameObject->GetTransform();
	_rend3D = _isStatic ? _rndScn->CreateStaticRenderer(_src, _nod) : _rndScn->CreateRenderer(_src);
	//_rend3D = _isStatic ? _rndScn->CreateRenderer(_src) : _rndScn->CreateRenderer(_src);

	_nod->Attach(_rend3D);
	//_rend3D->SetMaterial(_mat); TEMPORAL!
	//gameObject->SetRenderer(_rend3D);

}
//Hasta que haya lua
void LocoMotor::MeshRenderer::Start(std::string name, std::string file, std::string mat, bool isStatic)
{
	_name = name;
	_src = file;
	_mat = mat;
	_isStatic = isStatic;
}

/**
 * This function initializes the parameters of a MeshRenderer object using a vector of pairs.
 * @brief Initializes the parameters of a MeshRenderer object using a vector of pairs.
 * @param params A vector of pairs, where each pair contains a string key and a string value. These
 * pairs represent the parameters that are passed to the Init() function of the MeshRenderer class. The
 * function loops through each pair and checks the key to determine which member variable of the
 * MeshRenderer class to set with the
 */
void LocoMotor::MeshRenderer::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "name") {
			_name = params[i].second;
		}
		else if (params[i].first == "file") {
			_src = params[i].second;
		}
		else if (params[i].first == "mat") {
			_mat = params[i].second;
		}
	}
}

void LocoMotor::MeshRenderer::InitComponent() {

}

/**
 * The function returns a pointer to a 3D renderer object from a mesh renderer object.
 * @brief Returns a pointer to a 3D renderer object from a mesh renderer object.
 * @return An object of type OgreWrapper::Renderer3D* is being returned.
 */
OgreWrapper::Renderer3D* LocoMotor::MeshRenderer::GetRenderer() {
	return _rend3D;
}

/**
 * The function rotates a mesh renderer object using a given set of new rotation values.
 * @brief Rotates a mesh renderer object using a given set of new rotation values.
 * @param newRotation newRotation is a LMVector3 object that represents the new rotation to be applied
 * to the MeshRenderer. It contains three float values representing the rotation around the x, y, and z
 * axes respectively.
 */
void LocoMotor::MeshRenderer::Rotate(LMVector3 newRotation) {
	_nod->Rotate(newRotation.GetX(), newRotation.GetY(), newRotation.GetZ());
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Render() {
    
}

//OgreWrapper::Node* MeshRenderer::GetNode() {
//	return _nod;
//}


