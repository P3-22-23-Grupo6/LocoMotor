#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

using namespace LocoMotor;

const std::string Camera::name = "Camera";

LocoMotor::Camera::Camera()
{
	_scene = nullptr;
	_renderScn = nullptr;
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
}

void LocoMotor::Camera::InitComponent() {

	// La referencia del nodo de esta camara deberia ser el mismo que el nodo del gameObject
	_scene = gameObject->GetScene();
	_renderScn = _scene->GetRender();
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

	// Comprobar si hay asignado un target
	if (_target != nullptr) {
		// Actualizar posicion para que siga al target
		float x = _target->GetNode()->GetPosition_X();
		float y = _target->GetNode()->GetPosition_Y();
		float z = _target->GetNode()->GetPosition_Z();
		gameObject->SetPosition(LMVector3(x + _offset.GetX(), y + _offset.GetY(), z + _offset.GetZ()));
	}
}

void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset) {
	_target = target;
	_offset = offset;
}
