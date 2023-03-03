#include "RenderScene.h"
#include "OgreManager.h"
#include "Node.h"
#include "Renderer3D.h"
#include "Light.h"
#include "Camera.h"
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <iostream>

OgreWrapper::RenderScene::RenderScene(Ogre::SceneManager* scene) {
	_manager = scene;
	_mainCam = nullptr;
	_root = new OgreWrapper::Node(scene->getRootSceneNode());
}

OgreWrapper::RenderScene::~RenderScene() {
	delete _root;
	using iterador = std::map<std::string, Node*>::iterator;
	for (iterador it = _sceneStructure.begin(); it != _sceneStructure.end(); it = _sceneStructure.erase(it)) {
		delete it->second;
	}
}

void OgreWrapper::RenderScene::Render() {
	_mainCam->GetViewport()->update();
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode(std::string name) {
	if (_sceneStructure.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	Node* node = _root->CreateChild();
	_sceneStructure.insert({ name,node });
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::CreateNode(std::string name, std::string parent) {
	if (_sceneStructure.count(name) > 0 || name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	else if (_sceneStructure.count(parent) == 0) {
		std::cerr << "No node with name " << name << " found. Could not create child\n";
		return nullptr;
	}
	else if (parent == "Root") {
		return CreateNode(name);
	}
	Node* node = GetNode(name)->CreateChild();
	return node;
}

OgreWrapper::Node* OgreWrapper::RenderScene::GetNode(std::string name) {
	if (_sceneStructure.count(name) > 0) {
		std::cerr << "No node with the name " << name << " found\n";
		return nullptr;
	}
	if (name == "Root") {
		return _root;
	}

	return _sceneStructure.at(name);
}

OgreWrapper::Light* OgreWrapper::RenderScene::CreateLight() {
	return new Light(_manager->createLight(), Ogre::Light::LT_DIRECTIONAL);
}

OgreWrapper::Renderer3D* OgreWrapper::RenderScene::CreateRenderer(std::string mesh) {
	return new Renderer3D(_manager->createEntity(mesh));
}

OgreWrapper::Camera* OgreWrapper::RenderScene::CreateCamera(std::string name) {
	return new Camera(_manager->createCamera(name));
}

void OgreWrapper::RenderScene::SetActiveCamera(OgreWrapper::Camera* cam) {
	_mainCam = cam;
}

OgreWrapper::Camera* OgreWrapper::RenderScene::GetMainCamera() {
	return _mainCam;
}

void OgreWrapper::RenderScene::Prueba() {
	OgreWrapper::Node* mLightNode = CreateNode("Luz");
	OgreWrapper::Light* mLight = new Light(_manager->createLight(), Ogre::Light::LT_DIRECTIONAL);
	mLightNode->Attach(mLight);
	mLight->SetDiffuse(1, 1, 1);
	mLightNode->SetDirection(-1, -1, -1);
	Node* mCamNode = CreateNode("CamNode");
	Camera* cam = new Camera(_manager->createCamera("cam"));
	mCamNode->Attach(cam);
	//mCamNode->Attach (cam2);
	mCamNode->Translate (0, 0, 5);
	mCamNode->LookAt (0, 0, 0);
	SetActiveCamera (cam);
	OgreWrapper::Node* mCubeNode = CreateNode("Cubo");
	OgreWrapper::Renderer3D* cube = new Renderer3D (_manager->createEntity ("Feisar.mesh"));
	mCubeNode->Attach (cube);
	mCubeNode->Rotate(45, -90, 0);
	cube->SetMaterial("Racers/Falcon");
}

