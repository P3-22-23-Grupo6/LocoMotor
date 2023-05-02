#include "MeshRenderer.h"
#include "Renderer3D.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Scene.h"
#include "GameObject.h"
#include "LMVector.h"
#include "Transform.h"
#include "LogSystem.h"
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
	_nod = _rndScn->GetNode(gameObject->GetName());
	const Transform* aux = gameObject->GetTransform();
	_rend3D = _isStatic ? _rndScn->CreateStaticRenderer(_src, _nod) : _rndScn->CreateRenderer(_src);
	//_rend3D = _isStatic ? _rndScn->CreateRenderer(_src) : _rndScn->CreateRenderer(_src);
	if (_rend3D != nullptr) {
		_nod->Attach(_rend3D);
	}
	else {
		LogSystem::GetInstance()->Save(0, "Couldn't load mesh of name '" + _name + "' with filename '" + _src);
	}

	//_rend3D->SetMaterial(_mat); TEMPORAL!
	//gameObject->SetRenderer(_rend3D);

}
//Hasta que haya lua
void LocoMotor::MeshRenderer::Start(std::string name, std::string file, std::string mat, bool isStatic)
{
	
	_src = file;
	_mat = mat;
	_isStatic = isStatic;
}


void LocoMotor::MeshRenderer::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		
		if (params[i].first == "file") {
			_src = params[i].second;
		}
		else if (params[i].first == "mat") {
			_mat = params[i].second;
		}
		else if (params[i].first == "static") {
			_isStatic = true;
		}
			
	}
}

void LocoMotor::MeshRenderer::InitComponent() {

}


OgreWrapper::Renderer3D* LocoMotor::MeshRenderer::GetRenderer() {
	return _rend3D;
}

void LocoMotor::MeshRenderer::Rotate(LMVector3 newRotation) {
	_nod->Rotate(newRotation.GetX(), newRotation.GetY(), newRotation.GetZ());
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Render() {
    
}




