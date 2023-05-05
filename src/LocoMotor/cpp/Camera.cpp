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
	_cam = nullptr;
	_scene = nullptr;
	_renderScn = nullptr;
	_target = nullptr;
	_offset = LMVector3(0, 0, 0);
}

/**
 * This function initializes a camera component for a game object in a scene using OgreWrapper.
 */
void LocoMotor::Camera::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	InitComponent();
	for (auto & param : params) {
		if (param.first == "CameraMode") {
			try {
				int modeIndex = std::stoi(param.second);
				SetViewportRatio(1, modeIndex); //ViewportIndex = 1 TEMPORAL
			}
			catch (...) {
			}
		}
		else if (param.first == "FOV" || param.first == "fov") {
			try {
				float fov = std::stof(param.second);
				SetFOV(fov);
			}
			catch (...) {}
		}
		else if (param.first == "target") {
			target = param.second;
		}
		else if (param.first == "main") {
			gameObject->GetScene()->SetCamObj(gameObject);
		}
	}
	
}
void LocoMotor::Camera::InitComponent() {

	// La referencia del nodo de esta camara deberia ser el mismo que el nodo del gameObject
	_scene = gameObject->GetScene();
	_renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	OgreWrapper::Node* _node = _renderScn->GetNode(gameObject->GetName());

	//Crear camara
	_cam = _renderScn->CreateCamera(gameObject->GetName());
	_scene->SetSceneCam(_cam);
	//Attachear al nodo del gameObject
	_node->Attach(_cam);
	SetClippingPlane(1, 15000);

	//SetNode al gameObject

}

void LocoMotor::Camera::Start() {
	// Comprobar si hay asignado un target
	if (gameObject->GetScene()->GetObjectByName(target) != nullptr)
		SetTarget(gameObject->GetScene()->GetObjectByName(target), LMVector3(0, 15, 45));
}


void LocoMotor::Camera::PreUpdate(float dt) {

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
	_cam->SetClippingPlane((float) nearPlane, (float) farPlane);
}


void LocoMotor::Camera::SetFOV(float newFov) {
	if (newFov < 0.1f)
		newFov = 0.1f;
	if (newFov > 180.f)
		newFov = 180.f;
	_cam->SetFOV(newFov);
}

void LocoMotor::Camera::SetViewportRatio(int viewportIndex, int modeIndex) {
	_cam->SetViewportRatio(viewportIndex, modeIndex);
}
