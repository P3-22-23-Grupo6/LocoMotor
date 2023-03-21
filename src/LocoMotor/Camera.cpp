#include "Camera.h"
#include "LocoMotor_Ogre/include/Camera.h"
#include "RenderScene.h"
#include "Scene.h"

using namespace LocoMotor;

const std::string Camera::name = "Camera";

LocoMotor::Camera::Camera(Scene* scene, OgreWrapper::RenderScene* _renderScn) {
	
	//Crear nodo
	_node = _renderScn->CreateNode("ScnNode");
	
	//Crear camara
	scene->SetSceneCam(_renderScn->CreateCamera("ScnCam"));
	
	//Attachear al nodo del gameObject
	
	//SetNode al gameObject

}
