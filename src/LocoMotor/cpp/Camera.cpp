#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "Transform.h"
#include "RenderScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "OgreManager.h"
#include "Node.h"

using namespace LocoMotor;


LocoMotor::Camera::Camera()
{
	_cam = nullptr;
	_scene = nullptr;
	_target = nullptr;
	_initialOffset = LMVector3();
	camerMode = 0;
}


void LocoMotor::Camera::Init(std::vector<std::pair<std::string, std::string>>& params)
{
	InitComponent();
	for (auto & param : params) {
		if (param.first == "CameraMode") {//0: singlePlayer, 1: FirstPlayer, 2:SecondPlayer
			try {
				camerMode = std::stoi(param.second);
				SetViewportRatio(camerMode);
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
		else if (param.first == "initialOffset") {
			_initialOffset = LMVector3(0, 2, 8);
		}
		else if (param.first == "main") {
			gameObject->GetScene()->SetCamObj(gameObject);
		}
	}
	
}
void LocoMotor::Camera::InitComponent() {

	// La referencia del nodo de esta camara deberia ser el mismo que el nodo del gameObject
	_scene = gameObject->GetScene();
	OgreWrapper::RenderScene* _renderScn = _renderScn = OgreWrapper::OgreManager::GetInstance()->GetScene(gameObject->GetScene()->GetSceneName());
	OgreWrapper::Node* _node = _renderScn->GetNode(gameObject->GetName());
	if (_node == nullptr) {
		_node = _renderScn->CreateNode(gameObject->GetName());
	}
	//Crear camara
	_cam = _renderScn->CreateCamera(gameObject->GetName());
	_scene->SetSceneCam(_cam);
	//Attachear al nodo del gameObject
	_node->Attach(_cam);
	SetClippingPlane(1, 3000);

}

void LocoMotor::Camera::Start() {
	// Comprobar si hay asignado un target
	if (gameObject->GetScene()->GetObjectByName(target) != nullptr) {
		SetTarget(gameObject->GetScene()->GetObjectByName(target), _initialOffset);
	}
}


void LocoMotor::Camera::PreUpdate(float dt) {
	
	if (_target != nullptr) {
		// Actualizar posicion para que siga al target
		LMVector3 rotVec = _target->GetTransform()->GetRotation().Rotate(_initialOffset);
		gameObject->SetPosition(_target->GetTransform()->GetPosition() + rotVec);
		gameObject->SetRotation(_target->GetTransform()->GetRotation());
	}
	/*
	// Comprobar si hay asignado un target
	if (_target == nullptr) return;

	LMVector3 targetPos = _target->GetTransform()->GetPosition();
	LMQuaternion targetRot = _target->GetTransform()->GetRotation();
	LMVector3 rotVec = _target->GetTransform()->GetRotation().Rotate(_initialOffset);
	
	//Lerp Position
	LMVector3 finalPos;
	finalPos = finalPos.Lerp(gameObject->GetTransform()->GetPosition() , targetPos + rotVec, dt / 100.0f * 2.0f);
	gameObject->SetPosition(finalPos);
	//Slerp Rotation TODO SLERP IS NOT CORRECTLY IMPLEMENTED IN LMQUATERNION!!
	LMQuaternion finalRot;
	finalRot = finalRot.Slerp(gameObject->GetTransform()->GetRotation(), targetRot, dt / 100.0f * 2.0f);
	gameObject->SetRotation(targetRot);*/
}


void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset) {
	_target = target;
	offset = offset;
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

void LocoMotor::Camera::SetViewportRatio(int camerMode) {
	_cam->SetViewportRatio(camerMode);
}
