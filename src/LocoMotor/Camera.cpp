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
	_node = _renderScn->CreateNode("ScnNode");

	//Crear camara
	_scene->SetSceneCam(_renderScn->CreateCamera("ScnCam"));

	//Attachear al nodo del gameObject
	OgreWrapper::RenderEntity* renderObj = (OgreWrapper::RenderEntity*) this;

	_node->Attach(gameObject->GetNode());
	//gameObject->GetNode()->Attach(renderObj);

	//gameObject->GetNode()->Attach(renderObj);


	//_nod->Attach(renderObj);

	//SetNode al gameObject
}
