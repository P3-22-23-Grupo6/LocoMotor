
#include "MeshRederer.h"
#include "Renderer3D.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"

using namespace LocoMotor;

const std::string MeshRenderer::name = "MeshRenderer";

MeshRenderer::MeshRenderer(std::string name, std::string file,std::string mat,OgreWrapper::RenderScene* rndSc) {
	_name = name;
	_src = file;
	_mat = mat;
	_rndScn = rndSc;
}


void MeshRenderer::Start() {
	_nod = _rndScn->GetNode(_name);
	_rend3D = _rndScn->CreateRenderer(_src);
	_nod->Attach(_rend3D);
	//_rend3D->SetMaterial(_mat); TEMPORAL!
	//gameObject->SetRenderer(_rend3D);
}

OgreWrapper::Renderer3D* LocoMotor::MeshRenderer::GetRenderer() {
	return _rend3D;
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Render() {
    
}

//OgreWrapper::Node* MeshRenderer::GetNode() {
//	return _nod;
//}


