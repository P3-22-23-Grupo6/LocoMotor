
#include "MeshRenderer.h"
#include "Renderer3D.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Scene.h"
#include "GameObject.h"
#include "LMVector.h"
using namespace LocoMotor;

LocoMotor::MeshRenderer::MeshRenderer()
{
	_gobj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_rndScn = nullptr;
	_nod = nullptr;
	_rend3D = nullptr;
}


void MeshRenderer::Start() {
	_rndScn = gameObject->GetScene()->GetRender();
	_nod = _rndScn->GetNode(_name);
	_rend3D = _rndScn->CreateRenderer(_src);
	_nod->Attach(_rend3D);
	//_rend3D->SetMaterial(_mat); TEMPORAL!
	//gameObject->SetRenderer(_rend3D);

}
//Hasta que haya lua
void LocoMotor::MeshRenderer::Start(std::string name, std::string file, std::string mat)
{
	_name = name;
	_src = file;
	_mat = mat;
}

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

//OgreWrapper::Node* MeshRenderer::GetNode() {
//	return _nod;
//}


