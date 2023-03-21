#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "RenderScene.h"
#include "Scene.h"

using namespace LocoMotor;

const std::string Camera::name = "Camera";

LocoMotor::Camera::Camera(Scene* scene, OgreWrapper::RenderScene* _renderScn) {
	scene->SetSceneCam(_renderScn->CreateCamera("ScnCam"));
}
