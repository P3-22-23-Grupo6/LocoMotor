#include "Light.h"
#include "LocoMotor_Ogre/include/Light.h"
#include "Transform.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "OgreManager.h"
#include "Node.h"

using namespace LocoMotor;


LocoMotor::Light::Light() {
	_light = nullptr;
	_scene = nullptr;
}


void LocoMotor::Light::Init(std::vector<std::pair<std::string, std::string>>& params) {
	InitComponent();
}
void LocoMotor::Light::InitComponent() {

	// La referencia del nodo de esta camara deberia ser el mismo que el nodo del gameObject
	_scene = gameObject->GetScene();
	OgreWrapper::RenderScene* _renderScn = _renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	OgreWrapper::Node* _node = _renderScn->GetNode(gameObject->GetName());
	if (_node == nullptr) {
		_node = _renderScn->CreateNode(gameObject->GetName());
	}
	//Crear camara
	_light = _renderScn->CreateLight();
	//Attachear al nodo del gameObject
	_node->Attach(_light);
}

void LocoMotor::Light::Start() {
	_light->SetDiffuse(10.0, 10.0, 10.0);
}


void LocoMotor::Light::PreUpdate(float dt) {
}