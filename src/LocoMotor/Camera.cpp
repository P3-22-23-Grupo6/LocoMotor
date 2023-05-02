#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "Transform.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "OgreManager.h"
#include "Node.h"

using namespace LocoMotor;

/**
 * This is the constructor for the LocoMotor Camera class, initializing its member variables.
 */
LocoMotor::Camera::Camera()
{
	cam = nullptr;
	_scene = nullptr;
	_renderScn = nullptr;
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
}

/**
 * This function initializes a camera component for a game object in a scene using OgreWrapper.
 */
void LocoMotor::Camera::InitComponent() {

	// La referencia del nodo de esta camara deberia ser el mismo que el nodo del gameObject
	_scene = gameObject->GetScene();
	_renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	_node = _renderScn->GetNode(gameObject->GetName());

	//Crear camara
	cam = _renderScn->CreateCamera("ScnCam");
	_scene->SetSceneCam(cam);

	//Attachear al nodo del gameObject
	//OgreWrapper::RenderEntity* renderObj = cam;
	_renderScn->GetNode(gameObject->GetName())->Attach(cam);

	//SetNode al gameObject
}


void LocoMotor::Camera::Update(float dt) {

	// Comprobar si hay asignado un target
	if (_target != nullptr) {
		// Actualizar posicion para que siga al target
		LMVector3 rotVec = _target->GetTransform()->GetRotation().Rotate(_offset);
		gameObject->SetPosition(_target->GetTransform()->GetPosition() + rotVec);
		gameObject->SetRotation(_target->GetTransform()->GetRotation());
	}
}


void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset) {
	_target = target;
	_offset = offset;
}


void LocoMotor::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	cam->SetClippingPlane(nearPlane, farPlane);
}


void LocoMotor::Camera::SetFOV(float newFov) {
	cam->SetFOV(newFov);
}
