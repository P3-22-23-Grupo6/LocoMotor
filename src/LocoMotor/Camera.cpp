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

/**
 * This function updates the position and rotation of a camera to follow a target object.
 * 
 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
 * used to ensure that the movement and updates in the game are consistent across different hardware
 * and frame rates.
 */
void LocoMotor::Camera::Update(float dt) {

	// Comprobar si hay asignado un target
	if (_target != nullptr) {
		// Actualizar posicion para que siga al target
		auto rotVec = _target->GetTransform()->GetRotation().Rotate(_offset);
		gameObject->SetPosition(_target->GetTransform()->GetPosition() + rotVec);
		gameObject->SetRotation(_target->GetTransform()->GetRotation());
	}
}

/**
 * The function sets the target and offset for the camera of a LocoMotor object.
 * @brief Set the target and offset for the camera of a LocoMotor object.
 * @param target A pointer to a GameObject that the camera will follow as its target.
 * @param offset The offset is a vector that represents the distance and direction from the target
 * object's position where the camera should be positioned. It is used to adjust the camera's position
 * relative to the target object.
 */
void LocoMotor::Camera::SetTarget(GameObject* target, LMVector3 offset) {
	_target = target;
	_offset = offset;
}

/**
 * The function sets the clipping plane of a camera object.
 * @brief Set the clipping plane of a camera object.
 * @param nearPlane The distance from the camera to the nearest visible object in the scene. Any object
 * closer than this distance will not be visible in the rendered image.
 * @param farPlane The far clipping plane is the maximum distance from the camera at which objects will
 * be rendered. Any objects beyond this distance will not be visible in the rendered image.
 */
void LocoMotor::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	cam->SetClippingPlane(nearPlane, farPlane);
}

/**
 * This function sets the field of view (FOV) of a camera object.
 * @brief Set the field of view (FOV) of a camera object.
 * @param newFov newFov is a float variable representing the new field of view (FOV) value that will be
 * set for the camera. FOV is the extent of the observable world that is seen at any given moment
 * through the camera lens. It is usually measured in degrees and determines how much of the scene
 */
void LocoMotor::Camera::SetFOV(float newFov) {
	cam->SetFOV(newFov);
}
