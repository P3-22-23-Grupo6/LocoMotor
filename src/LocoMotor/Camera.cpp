#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

using namespace LocoMotor;

const std::string Camera::name = "Camera";

LocoMotor::Camera::Camera(Scene* __scene, OgreWrapper::RenderScene* __renderScn) {

	// Guardar variables para usarlas en el inicializador del componente

	_scene = __scene;
	_renderScn = __renderScn;
}

void LocoMotor::Camera::InitComponent() {

	//Crear nodo
	_node = _renderScn->CreateNode("CamNode");

	//Crear camara
	_scene->SetSceneCam(_renderScn->CreateCamera("ScnCam"));

	//Attachear al nodo del gameObject
	//OgreWrapper::RenderEntity* renderObj = (OgreWrapper::RenderEntity*) this;
	//gameObject->GetNode()->Attach(renderObj);

	//SetNode al gameObject
}

void LocoMotor::Camera::Update(float dt) {

	if (_node != nullptr) {
		float x = gameObject->GetNode()->GetPosition_X();
		float y = gameObject->GetNode()->GetPosition_Y();
		float z = gameObject->GetNode()->GetPosition_Z();

		_node->SetPosition(x, y, z);
	}
}
