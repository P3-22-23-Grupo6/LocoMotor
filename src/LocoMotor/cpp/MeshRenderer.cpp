#include "MeshRenderer.h"
#include "Renderer3D.h"
#include "OgreManager.h"
#include "RenderScene.h"
#include "Node.h"
#include "Scene.h"
#include "GameObject.h"
#include "LMVector.h"
#include "LMVectorConverter.h"
#include "Transform.h"
#include "LogSystem.h"
using namespace LocoMotor;


LocoMotor::MeshRenderer::MeshRenderer()
{
	_gobj = nullptr;
	_name = "";
	_src = "";
	_mat = "";
	_rndScn = nullptr;
	_node = nullptr;
	_rend3D = nullptr;
	_isStatic = false;
}


 
void MeshRenderer::PreStart() {


}

void LocoMotor::MeshRenderer::Start(std::string name, std::string file, std::string mat, bool isStatic)
{
	_src = file;
	_mat = mat;
	_isStatic = isStatic;
}


void LocoMotor::MeshRenderer::Init(std::vector<std::pair<std::string, std::string>>& params) {
	bool visible = true;
	for (int i = 0; i < params.size(); i++) {
		
		if (params[i].first == "file") {
			_src = params[i].second;
		}
		else if (params[i].first == "mat") {
			_mat = params[i].second;
			_rend3D->SetMaterial(_mat);
		}
		else if (params[i].first == "static") {
			_isStatic = true;
		}
		else if (params[i].first == "invisible") {
			visible = false;
		}
	}

	_rndScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	_node = _rndScn->GetNode(gameObject->GetName());
	if (_node == nullptr) {
		_node = _rndScn->CreateNode(gameObject->GetName());
	}
	if (_src == "") {
		LogSystem::GetInstance()->Save(0, "No mesh added for MeshRenderer in gameObject '" + gameObject->GetName() + "'");
		return;
	}

	_rend3D = _isStatic ? _rndScn->CreateStaticRenderer(_src, _node) : _rndScn->CreateRenderer(_src);
	if (_mat != "") _rend3D->SetMaterial(_mat);
	if (_rend3D != nullptr) 
	{
		_node->Attach(_rend3D);
		if (!visible)
			_rend3D->SetVisible(false);
	}
	else {
		LogSystem::GetInstance()->Save(0, "Couldn't load mesh of name '" + _name + "' with filename '" + _src);
	}
}
void LocoMotor::MeshRenderer::InitRuntime(std::string meshSource, std::string materialName) {
	bool visible = true;
	_src = meshSource;
	_mat = materialName;

	_rndScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	_node = _rndScn->GetNode(gameObject->GetName());
	if (_node == nullptr) {
		_node = _rndScn->CreateNode(gameObject->GetName());
	}
	if (_src == "") {
		LogSystem::GetInstance()->Save(0, "No mesh added for MeshRenderer in gameObject '" + gameObject->GetName() + "'");
		return;
	}

	_rend3D = _isStatic ? _rndScn->CreateStaticRenderer(_src, _node) : _rndScn->CreateRenderer(_src);
	if(materialName != "") _rend3D->SetMaterial(materialName);
	if (_rend3D != nullptr ) {
		_node->Attach(_rend3D);
		if (!visible)
			_rend3D->SetVisible(false);
	}
	else {
		LogSystem::GetInstance()->Save(0, "Couldn't load mesh of name '" + _name + "' with filename '" + _src);
	}
}

void LocoMotor::MeshRenderer::InitComponent() {

}


OgreWrapper::Renderer3D* LocoMotor::MeshRenderer::GetRenderer() {
	return _rend3D;
}

void LocoMotor::MeshRenderer::ChangeMaterial(std::string newMaterial) {
	_rend3D->SetMaterial(newMaterial);
}

void LocoMotor::MeshRenderer::SetVisible(bool value) {
	_rend3D->SetVisible(value);
}

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Render() {
    
}
void MeshRenderer::ChangeTexOffset(std::string matName, float newX, float newY) {
	OgreWrapper::OgreManager::GetInstance()->ChangeTexOffset(matName, newX, newY);
}
void MeshRenderer::CreateBillboard(LMVector3 billPos, std::string matName){
	
}




