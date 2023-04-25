#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "Transform.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "Node.h"

using namespace LocoMotor;

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
		auto rotVec = _target->GetTransform()->GetRotation().Rotate(_offset);
		gameObject->SetPosition(_target->GetTransform()->GetPosition() + rotVec);
		gameObject->SetRotation(_target->GetTransform()->GetRotation());
	}
}

void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset) {
	_target = target;
	_offset = offset;
}
