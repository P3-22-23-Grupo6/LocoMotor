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
	_node = gameObject->GetNode();

	//Crear camara
	OgreWrapper::Camera* cam = _renderScn->CreateCamera("ScnCam");
	_scene->SetSceneCam(cam);


	//Attachear al nodo del gameObject
	//OgreWrapper::RenderEntity* renderObj = cam;
	gameObject->GetNode()->Attach(cam);

	//SetNode al gameObject
}

void LocoMotor::Camera::Update(float dt) {

	if (_node != nullptr) {
		Transform transform = gameObject->GetTransform();

		_node->SetPosition(transform.position.GetX() + 10, transform.position.GetY(), transform.position.GetZ());
	}
}
